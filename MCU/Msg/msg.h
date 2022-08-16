//������ ���������
#ifndef MSG_H
#define MSG_H

#include "stm32f4xx.h"

//defines
#define MAXMESSAGE  0xFFFF


const enum class EventSrc : u32 {
	KEYBOARD,
	REPAINT,
	TIMER,
	DATAUPDATE
};

//����������
/*���� ����������
   P |  UP   | ESC
--------------------
LEFT | ENTER | RIGHT
--------------------
  F1 | DOWN  |   F2
*/
/*
const enum class ModbusReadRegsDefs {
	CMD_POS = 1,
	ANSW_BYTES_POS = 2,
	ANSW_DATA_POS = 3
};*/

const enum class KeyCodes : u32 {
	None    = 0, //������ ������� �� ������
	ESC     = 1, //������ (� ����� �� ���� ������� ���� �����)
	Up      = 72, //2 //������� �����
	P       = 3, //����� ����
	Right   = 4, //������� ������
	ENT     = 13,//5 //����� ������
	Left    = 6, //������� �����
	F2      = 7, //�������������� ������� F2
	Down    = 80,//8 //������� ����
	F1      = 9 //�������������� ������� F1
};

typedef struct {//���, ����� ���� �������� ;-)
  u16 x;
  u16 y;
  u8  Key;
} TMouseState;

typedef struct {//��������� ���������
  u32 Event;//��� ���������
  //��������� ���������
  u32 p1;//������ ��������
  u32 p2;//������ ��������
} TMessage;

#define msg_buff_size 32 //������ ������ ���������

class Msg {
	public:
		static void send_message(u32 event, u32 p1, u32 p2);//�������� ��������� � ����� �������
		static bool get_message(TMessage* m);//������� ������ � ������� ���������
		static void clear_msg_queue();//������� ������� ���������
	private:
		static TMessage Messages[msg_buff_size];//������� ���������
};

#endif