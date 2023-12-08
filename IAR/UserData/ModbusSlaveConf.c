#include "Intmash_bastypes.h" 
#include "STM32F4xx_intmash_MBbasicCommands.h"
#include "STM32F4xx_Intmash_USART.h"
#include "STM32F4xx_Intmash_Flash.h"
#include "ModbusSlave.h"
#include "CalibrationData.h"
#include "FlashData.h"
#include "RAMdata.h"
#include "ModbusMasterConf.h"
#include "crc16.h"

//��������� ��������� UART � �������
Intmash_Usart UART1toRS485; // ����� �� ������������� RS485
ModbusSlaveType RS485slave;
tU8 StartBootLoader(ModbusSlaveType* Slave);

//����� ������������ ������ +1
ModbusCommandHandlerType ModbusCommands[6]={
  {ModbusMemRead, 0x03},
  {ModbusMemWrite, 0x10},
  {GetDeviceID, 0x11},
  {StartBootLoader, 0xB0},
  {0, 0},
}; 

#define INTERFACE_DEFAULT_SETTINGS (u32)(0x00000401)

void ModbusClientInit(void) //������ ������������� ���������, ������
{ 
  //RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3 | RCC_APB1Periph_USART2, ENABLE);//
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);//
   
  tU32Union InterfaceSettings;
  
  //USART1, OptRS485
  UART1toRS485.USARTx = USART1;
  InterfaceSettings.I = (FlashStatus.Bits.FLASH_DATA_ERR)
    ? INTERFACE_DEFAULT_SETTINGS
    : FLASH_DATA.Modbus_U1_RS485;
 
  RS485slave.SlaveAddress = InterfaceSettings.B[0];    
  UART1toRS485.USART_BaudRate = USARTbaudRate[InterfaceSettings.B[1]];
  UART1toRS485.USART_StopBits = InterfaceSettings.B[2];
  UART1toRS485.USART_Parity = InterfaceSettings.B[3];

  UART1toRS485.DMAy_StreamRX = DMA2_Stream5;
  UART1toRS485.DMAy_StreamTX = DMA2_Stream7;
  
  UART1toRS485.DMA_channel = DMA_Channel_4;
  UART1toRS485.DMA_FLAGS_RX = DMA_FLAG_FEIF5 | DMA_FLAG_DMEIF5 | DMA_FLAG_TEIF5 | DMA_FLAG_HTIF5 | DMA_FLAG_TCIF5;
  UART1toRS485.DMA_FLAGS_TX = DMA_FLAG_FEIF7 | DMA_FLAG_DMEIF7 | DMA_FLAG_TEIF7 | DMA_FLAG_HTIF7 | DMA_FLAG_TCIF7;
  UART1toRS485.GPIOxDIR = GPIOA;
  UART1toRS485.GPIO_PinDIR = GPIO_Pin_8;
  UART1toRS485.PolarityDIR = POLARITY_HI; //��������� ���������� 
  UsartDriverInit (&UART1toRS485); //������������� ���������
  UsartRecieve (&UART1toRS485, &RS485slave.Buffer[0]);//��������� �� ����� � ����  
}


//���������� USART �� ������������� RS485
void USART1_IRQHandler(void)
{
  tU8 MsgSize = UsartTxRxFinish(&UART1toRS485);//���������� ��� ���������: ����� ��� ������� MsgSize ����. ; 
        
  if(MsgSize){//���� ��������  
    //if (LED2_ST) LED2_OFF; else LED2_ON; //�������� �������� 
    /*
    if (FLASH_DATA.Retranslate != 0) {
      //���� ������������ �������� � ������� �������� ��������� �� ������� ������
      if ((crc16((tU8*)RS485slave.Buffer, MsgSize) == 0) && (RS485slave.Buffer[0] == RS485slave.SlaveAddress))
      {
        //fRtrWaitResp =1;
        //RTR_size = MsgSize;
        //for(tU8 i=0; i<MsgSize;i++) {slot_RTR.OutBuf[i] = RS485slave.Buffer[i];}    
        //slot_RTR.Flags.Bits.SKIP_SLOT = 0; //�������� ����
      }
      else UsartRecieve(&UART1toRS485, &RS485slave.Buffer[0]);
    }
    else*/
    {//�������� ������� �������������, ���������� ������ ������ ��� ��������
      MsgSize = ModbusCommandDecode(&RS485slave, MsgSize, ModbusCommands); 
      //���� ���� ��� ���������� - ����������, ���� ��� - �������� �� �����.
      if(MsgSize) UsartTransmit(&UART1toRS485, &RS485slave.Buffer[0], MsgSize);
      else UsartRecieve(&UART1toRS485, &RS485slave.Buffer[0]);      
    }
  }  
  else  UsartRecieve(&UART1toRS485, &RS485slave.Buffer[0]);//���� ����������, �������� �� �����. 
}

//������� ��� ������ ���������
void RebootMBSlave(void)
{
  UsartTxRxFinish(&UART1toRS485); //�������� ��������� � ��� ����
  UsartRecieve(&UART1toRS485, &RS485slave.Buffer[0]); //��������� �� �����
}

__no_init char BootLoaderStart[6] @ "BOOT_CMD";
tU8 StartBootLoader(ModbusSlaveType* Slave) {
  BootLoaderStart[0] = 0xA5;
  BootLoaderStart[1] = 0x5A;
  BootLoaderStart[2] = 0xA5;
  BootLoaderStart[3] = 0x5A; 
  FrameEndCrc16((tU8*)BootLoaderStart, 6);
  NVIC_SystemReset();
}

void BootLoadCmdFillZero(void) {
  BootLoaderStart[0] = 0x00;
  BootLoaderStart[1] = 0x00;
  BootLoaderStart[2] = 0x00;
  BootLoaderStart[3] = 0x00; 
  BootLoaderStart[4] = 0x00;
  BootLoaderStart[5] = 0x00;
}