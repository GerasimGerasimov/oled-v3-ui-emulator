#ifndef MODBUSMASTER_H
#define MODBUSMASTER_H
#include "Intmash_bastypes.h"

//���� ��� ����������� ������� ����������
typedef struct {  
  void (*OnTimeOut)(void);//��������� ������� ���������� ���� ������ �� ��������
  void (*OnRecieve)(void);//��� ������ ����� ��������� �����-�� ������
  u8 InBufLen;//������� ������ �������
} MBmasterSlotType;

#endif
