/**
  ******************************************************************************
  * @file    STM32F4xx_Intmash_SPI_FRAMkey.h
  * @author  IMD, Erlina
  * @version V1.0.0
  * @date    16-06-2019
  * @brief   ���� �������� �����������, ������� � �������������� ������� ��� 
  * ������ � ������ ���������� �� Fram FM25040B-G
  ******************************************************************************
  * @��� � ���� ��������:
  * - ������� ���� ������ ����������������, ������� �������� ������������ 
  * ��������� FRAM. ����� � init.c ��������������� ����� ����������������. 
  * - � ����� fram.h ������������� ������� ��� �������� ���������� ��� ������ 
  * ���������� ���������� (���� ����������).
  * - � ������ ������������� ���������� ���������� ������� CheckFRAMkey(), �������
  * ��������� ������ ����� ���������� � ����������� ������, �� ��� ���������.
  * - ���� ������� ������� ������ �� ����������� flash ������ ����������, 
  * ������� ������� FRAMwriteMassive ��� ������ � �������� � ��������� ������� 
  * ����� ���������� ���������� ������ �� flash ������ (����� �� ����� 
  * ���������� ������ ���� ���������� ������)
  * - ��� �� ������������� ������� ����� �������� �� ������������� (��������, 
  * ���� flash-������ ���������� - �������� � �� ������� �� ����� ����������, 
  * �������������� ������ � � ������� FRAMreadMassive)
  ******************************************************************************
  * @�������:
  *
  * 
  ******************************************************************************
  */

#ifndef STM32F4xx_Intmash_SPI_FRAMkey_H
#define STM32F4xx_Intmash_SPI_FRAMkey_H

#include "stm32f4xx.h"//���������� StdPeriph_Driver
#include "Intmash_bastypes.h" 

#define FRAM_KEY_DEFAULT_ADDR 0
#define FRAM_KEY_MAIN_SECTOR  0 //�������� ������
#define FRAM_KEY_BKP_SECTOR   1 //���������
#define FRAM_KEY_SECTOR_SIZE  256

//��������� ����� 
#define MAIN_SECTOR_ERROR  B0     
#define BKP_SECTOR_ERROR   B1    

typedef struct 
{
  SPI_TypeDef* SPIx;
  GPIO_TypeDef* GPIOxCS;
  tU16 Pin_CS; 
} SPI_FRAMkey_InitStruct;  

extern tU8Union SPI_FRAMkey_Status;

void SPI_FRAMkey_Init(SPI_FRAMkey_InitStruct * Key);
void SPI_FRAMkey_Write(tU8 * Src, tU8 Sector, tU8 Addr, tU16 ByteNum);
void SPI_FRAMkey_Read(tU8 * Dst, tU8 Sector, tU8 Addr, tU16 ByteNum);
void SPI_FRAMkey_Check(void);



#endif 