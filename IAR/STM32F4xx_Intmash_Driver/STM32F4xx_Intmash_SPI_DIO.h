/**
  ******************************************************************************
  * @file    STM32F4xx_Intmash_SPI_DIO.h
  * @author  IMD, Erlina
  * @version V1.0.0
  * @date    16-06-2019
  * @brief   ���� �������� ������� ��� ������ ����������� ������� �������� ����� SPI 
  ******************************************************************************
  * @�������:
  *
  * 
  ******************************************************************************
  * @��� � ���� ��������:
  * - ������� ���������� ������� ������� UserDIOst ���� Intmash_DIO � ���������. ������� ������� SpiDioInit();
  * - ����� ���������� DIO_Reset(&Intmash_DIO);  
  * - ��� ������������ SPI ���������� ������� SPI_DIOdriverInit(&Intmash_DIO);   
  * - � ������� ������ ���������� (��� ����� ������ � ����������� �������������� 
  * ������) ���������� ������� DIOtransactionStart(&Intmash_DIO), �������������� ������ ���������. 
  * ������� ������ ������� �������� �� 2 - ��� ������� ������ ���������� ������ 
  * � ��������� ���������� �������. ������� ���������� 1, ���� ��������� DI  
  * ���������, ����� ����������� ����� ������ DO � ������������ ��������. �������
  * ���������� 0, ���� � ������� ������ ����������� ����� ������� ����� �� � DIO 
  * 
  * ������� ������ � ��������: ������� DIOtransactionStart ���������� � ������ �������� ���-�� � ����.
  * � ��� ���������� ������ �� ����������� ������� � ������ ���������
  ******************************************************************************
  */
#ifndef STM32F4xx_Intmash_SPI_DIO_H
#define STM32F4xx_Intmash_SPI_DIO_H
  
#include "stm32f4xx.h"
#include "Intmash_bastypes.h" 

//������� ��������� ������/�������
extern tU16Union SPI_DIO_Inputs;
extern tU16Union SPI_DIO_Outputs;

/*
��������� ������������ ��������
*/
typedef struct 
{
  //������������ ��������� SPI
  //���������� ����������������!!!
  SPI_TypeDef* SPIx;
  //��������� �� ������, ������������ ��� ������� ������, ����=0 - �������� ��� ������� (Basic Timers: 6 ��� 7)
  TIM_TypeDef* LatchTimer;
  //�����, ������������ ��� ���������� ���������� ���������� (���������� ����������������!!!)
  GPIO_TypeDef* DO_OE_Port;
  GPIO_TypeDef* DO_RST_Port;
  GPIO_TypeDef* DO_LCLK_Port;
  GPIO_TypeDef* DI_CE_Port;
  GPIO_TypeDef* DI_LCLK_Port;
  //���� ������, ������������ ��� ���������� ���������� ���������� (���������� ����������������!!!)
  tU16 DO_OE_Pin;
  tU16 DO_RST_Pin;
  tU16 DO_LCLK_Pin;
  tU16 DI_CE_Pin;
  tU16 DI_LCLK_Pin;   
  //��������� SPI
  tU16 SPI_DataSize;//���������� ������/������� (�� ��������� SPI_DataSize_8b)
  tU16 SPI_BitOrder;//������� ����������� � ��������� ��������� (�� ��������� SPI_FirstBit_MSB)
  //��������� ������� (����=0 - �������� ��� �������)
  tU16 LatchTimerDelay;  
  //��������� ������� ������ ������/�������
  tU8  InputsMode;
  tU8  OutputsMode;   
} SPI_DIO_InitStruct;  

#define DIO_MODE_NORMAL  0
#define DIO_MODE_INVERT  1

//����������� ����� ��� ���������� ������/�������
#define DIN0   Bits.B0  
#define DIN1   Bits.B1   
#define DIN2   Bits.B2
#define DIN3   Bits.B3
#define DIN4   Bits.B4
#define DIN5   Bits.B5
#define DIN6   Bits.B6
#define DIN7   Bits.B7
#define DIN8   Bits.B8
#define DIN9   Bits.B9
#define DIN10  Bits.B10
#define DIN11  Bits.B11
#define DIN12  Bits.B12
#define DIN13  Bits.B13
#define DIN14  Bits.B14
#define DIN15  Bits.B15

#define DOUT0   Bits.B0
#define DOUT1   Bits.B1
#define DOUT2   Bits.B2
#define DOUT3   Bits.B3
#define DOUT4   Bits.B4
#define DOUT5   Bits.B5
#define DOUT6   Bits.B6
#define DOUT7   Bits.B7
#define DOUT8   Bits.B8
#define DOUT9   Bits.B9
#define DOUT10  Bits.B10
#define DOUT11  Bits.B11
#define DOUT12  Bits.B12
#define DOUT13  Bits.B13
#define DOUT14  Bits.B14
#define DOUT15  Bits.B15

//�������������� �������
void SPI_DIO_DriverInit(SPI_DIO_InitStruct * DIOstr);//������������� ��������
void SPI_DIO_Reset(void);//����� �������� ���������� � ��������� � �������� ���������
tU8  SPI_DIO_Processing(void);//����� DI, �������� DO, ������� � ��������. 
void SPI_DIO_ProcessingTimer(void);//����� DI, ������� � ��������.

#endif 