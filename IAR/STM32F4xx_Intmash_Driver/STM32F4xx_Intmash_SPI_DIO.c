/**
  ******************************************************************************
  * @file    STM32F4xx_Intmash_SPI_DIO.�
  * @author  IMD, Erlina
  * @version V1.0.0
  * @date    16-06-2019
  * @brief   ���� �������� ������� ��� ������ ����������� ������� �������� ����� SPI 
  ******************************************************************************  
  * @�������:
  *
  * 
  ******************************************************************************
  */
#include "STM32F4xx_Intmash_SPI_DIO.h"

//���������� ������
tU16Union SPI_DIO_Inputs;
tU16Union SPI_DIO_Outputs;
//������������ ��������� SPI
SPI_TypeDef* SPI_DIO;
//��������� �� ������, ������������ ��� ������� ������, ����=0 - �������� ��� ������� (Basic Timers: 6 ��� 7)
TIM_TypeDef* Timer_DIO;
tU16 Timer_Delay;  
//�����, ������������ ��� ���������� ���������� ���������� 
GPIO_TypeDef* Port_DO_OE;
GPIO_TypeDef* Port_DO_RST;
GPIO_TypeDef* Port_DO_LCLK;
GPIO_TypeDef* Port_DI_CE;
GPIO_TypeDef* Port_DI_LCLK;
//���� ������, ������������ ��� ���������� ���������� ���������� 
tU16 Pin_DO_OE;
tU16 Pin_DO_RST;
tU16 Pin_DO_LCLK;
tU16 Pin_DI_CE;
tU16 Pin_DI_LCLK;   
//��������� ������� ������ ������/�������
tU8  InputsPolarity;
tU8  OutputsPolarity; 

 /* ���� ������������ ������� ��� ��������
  ******************************************************************************
  * ST - ��������� �������
  * UP - ��������� ������ � 1
  * DWN - ��������� ������ � 0  
  ******************************************************************************/
#define DO_OE_ST   (Port_DO_OE->ODR & Pin_DO_OE)
#define DO_OE_UP   Port_DO_OE->BSRRL = Pin_DO_OE
#define DO_OE_DWN  Port_DO_OE->BSRRH = Pin_DO_OE

#define DO_RST_ST   (Port_DO_RST->ODR & Pin_DO_RST)
#define DO_RST_UP   Port_DO_RST->BSRRL = Pin_DO_RST
#define DO_RST_DWN  Port_DO_RST->BSRRH = Pin_DO_RST

#define DO_LCLK_ST   (Port_DO_LCLK->ODR & Pin_DO_LCLK)
#define DO_LCLK_UP   Port_DO_LCLK->BSRRL = Pin_DO_LCLK
#define DO_LCLK_DWN  Port_DO_LCLK->BSRRH = Pin_DO_LCLK

#define DI_CE_ST     (Port_DI_CE->ODR & Pin_DI_CE)
#define DI_CE_UP     Port_DI_CE->BSRRL = Pin_DI_CE
#define DI_CE_DWN    Port_DI_CE->BSRRH = Pin_DI_CE

#define DI_LCLK_ST   (Port_DI_LCLK->ODR & Pin_DI_LCLK)
#define DI_LCLK_UP   Port_DI_LCLK->BSRRL = Pin_DI_LCLK
#define DI_LCLK_DWN  Port_DI_LCLK->BSRRH = Pin_DI_LCLK


/**
  * @brief  ������� ���������� ������� ���������� � �������� ��������� 
  * @param  None
  * @retval None
  */
void SPI_DIO_Reset(void)
{
  DO_OE_UP;
  DO_RST_DWN;
  DO_LCLK_DWN;  
  DI_CE_UP;
  DI_LCLK_UP;  
}

/**
  * @brief  ��������� SPI ��� ������ ����������� �������/��������
  * ������ � ������ ���������� ������(�������� ����� ��� DO, ����� ������ �� DI)
  * ������ ������ 8 ���� 16 ��� (�� 16 ������ � ������� ��������)
  * ���������� ������ 256, �������� ���������� ��� ������ �� 1000 ���/������� (328 125 bps)
  * @param  None
  * @retval None
  */
//******************************************************************************
#define LATCH_TIM_BUS_CLK ((tU32)84000000)
#define LATCH_TIM_CLK     ((tU32)1000000)
#define LATCH_TIM_PSC     ((LATCH_TIM_BUS_CLK / LATCH_TIM_CLK) - 1)
void SPI_DIO_DriverInit(SPI_DIO_InitStruct * DIOstr)
{  
  SPI_DIO_Inputs.I = 0;
  SPI_DIO_Outputs.I = 0;
  //������������ ��������� SPI
  SPI_DIO = DIOstr->SPIx;
  //��������� �� ������, ������������ ��� ������� ������, ����=0 - �������� ��� ������� (Basic Timers: 6 ��� 7)
  Timer_DIO = DIOstr->LatchTimer;
  Timer_Delay = DIOstr->LatchTimerDelay; 
  //�����, ������������ ��� ���������� ���������� ����������
  Port_DO_OE = DIOstr->DO_OE_Port;
  Port_DO_RST = DIOstr->DO_RST_Port;
  Port_DO_LCLK = DIOstr->DO_LCLK_Port;
  Port_DI_CE = DIOstr->DI_CE_Port;
  Port_DI_LCLK = DIOstr->DI_LCLK_Port;
  //���� ������, ������������ ��� ���������� ���������� ����������
  Pin_DO_OE = DIOstr->DO_OE_Pin;
  Pin_DO_RST = DIOstr->DO_RST_Pin;
  Pin_DO_LCLK = DIOstr->DO_LCLK_Pin;
  Pin_DI_CE = DIOstr->DI_CE_Pin;
  Pin_DI_LCLK = DIOstr->DI_LCLK_Pin;   
  //��������� ������� ������ ������/�������
  InputsPolarity = DIOstr->InputsMode;
  OutputsPolarity = DIOstr->OutputsMode; 

  SPI_DIO_Reset();

  //������������� SPI
  SPI_InitTypeDef  SPI_InitStructure;
  if(SPI_DIO == SPI1) RCC_APB2PeriphClockCmd( RCC_APB2Periph_SPI1, ENABLE);
  else if(SPI_DIO == SPI2) RCC_APB1PeriphClockCmd( RCC_APB1Periph_SPI2, ENABLE);
  else if(SPI_DIO == SPI3) RCC_APB1PeriphClockCmd( RCC_APB1Periph_SPI3, ENABLE);
  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
  SPI_InitStructure.SPI_DataSize = DIOstr->SPI_DataSize;
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;
  SPI_InitStructure.SPI_FirstBit = DIOstr->SPI_BitOrder;
  SPI_InitStructure.SPI_CRCPolynomial = 7;
  SPI_Init(SPI_DIO, &SPI_InitStructure);
  SPI_Cmd(SPI_DIO, ENABLE);

  //������������� ������� �������
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;  
  if((Timer_DIO != 0) && (Timer_Delay != 0))
  {
    if(Timer_DIO == TIM6) RCC_APB1PeriphClockCmd( RCC_APB1Periph_TIM6, ENABLE);
    else if(Timer_DIO == TIM7) RCC_APB1PeriphClockCmd( RCC_APB1Periph_TIM7, ENABLE);    
    
    TIM_TimeBaseStructure.TIM_Prescaler = LATCH_TIM_PSC;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseStructure.TIM_Period = Timer_Delay;
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
    
    TIM_TimeBaseInit(Timer_DIO, &TIM_TimeBaseStructure);
    TIM_SelectOnePulseMode(Timer_DIO, TIM_OPMode_Single);
    Timer_DIO->SR = 0;
    TIM_ITConfig(Timer_DIO, TIM_IT_Update, ENABLE);
    TIM_Cmd(Timer_DIO, DISABLE);       
  }   
}

/**
  * @brief  ������� ���������� ������ �������� ���������� ���������� ����������, 
  *         ���������, ���������� ������ � ��������� DIO. 
  * @param  None
  * @retval ������� ���������� 1, ���� ��������� DI ���������, ����� ����������� 
  * ����� ������ DO � ������������ ��������. ������� ���������� 0, ���� � ������� ������
  * ����������� ����� ������� ����� �� � DIO.
  */

tU8 SPI_DIO_Processing()
{
  tU8 RetVal = 0;
  //���� �� �������� ����� ��������� ��������� ���������� �������, ������ 
  //��������� �������� ������ � ������� ��������� � ������
  //�������������� ������ ��������� ���������
  if (DO_OE_ST)
  {    
    //������ ����� ��������� ����� ����������� ���������� �������
    if (DO_RST_ST)
    {
      //���� ����� ��� ������� - ������� ���������� ���������� ���������� ������� ������, ����� �������� outpit enable
      //��� ��  - ������� ��������� ������������ ���������� ������, ����� ����������� ���������� ����� 
      if (DO_LCLK_ST) {DO_OE_DWN; DI_LCLK_DWN;} 
      else {DO_LCLK_UP; DI_CE_DWN;}
    }
    else DO_RST_UP;//���� ����� �� ������� - ���������
  }
  else//���� �������� ����� ��������� ���������, �.�. ������������� ������
  {
    //���� ��������� ���� ������� � ������ ��������� - ������ ��� � ��������� ����� ����� ������
    if (DO_LCLK_ST) 
    {
      DO_LCLK_DWN;
      DI_LCLK_UP;
      if(OutputsPolarity == DIO_MODE_NORMAL) SPI_DIO->DR = SPI_DIO_Outputs.I;
      else if(OutputsPolarity == DIO_MODE_INVERT) SPI_DIO->DR = ~(SPI_DIO_Outputs.I);      
      //����� �������� ����� ����� - �������� ������ ���������� �������� (���� �������� ����)
      if(Timer_Delay) Timer_DIO->CR1 |= (u16)TIM_CR1_CEN;    
    }
    //���� ��������� ���� ������� �� � ������ ��������� - ��� ���� �� ������, ����������
    else 
    {
      DO_LCLK_UP;//������� ����� �������
      DI_LCLK_DWN; 
      if(InputsPolarity == DIO_MODE_NORMAL) SPI_DIO_Inputs.I = SPI_DIO->DR;
      else if(InputsPolarity == DIO_MODE_INVERT)  SPI_DIO_Inputs.I = ~(SPI_DIO->DR);      
      RetVal = 1;
    } 
  }  
  return RetVal;
}

void SPI_DIO_ProcessingTimer()
{
  DO_LCLK_UP;//������� ����� �������
  DI_LCLK_DWN;  
  if(InputsPolarity == DIO_MODE_NORMAL) SPI_DIO_Inputs.I = SPI_DIO->DR;
  else if(InputsPolarity == DIO_MODE_INVERT)  SPI_DIO_Inputs.I = ~(SPI_DIO->DR); 
}
