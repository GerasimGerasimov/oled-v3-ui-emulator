//������ ���������
#ifndef MSG_H
#define MSG_H

#include "stm32f4xx.h"

//defines
#define MAXMESSAGE  0xFFFF
#define LBCLICK     MAXMESSAGE
#define LBDOWN      MAXMESSAGE-1
#define LBUP        MAXMESSAGE-2
#define MDRAG       MAXMESSAGE-3
#define MMOVE       MAXMESSAGE-4
#define TICK        MAXMESSAGE-5
#define CHANGE      MAXMESSAGE-6
#define MENUCLOSE   MAXMESSAGE-7
#define BUTTONCLICK MAXMESSAGE-8
#define EDITENTER   MAXMESSAGE-9
#define UNFOCUS     MAXMESSAGE-10
#define SETFOCUS    MAXMESSAGE-11
#define KEYBOARD    MAXMESSAGE-12
#define CHEKCHANGE  MAXMESSAGE-13
#define HIDECURSOR  MAXMESSAGE-14
#define LISTCLICK   MAXMESSAGE-15
#define COLLSTEXIT  MAXMESSAGE-16
#define OPENWINDOW  MAXMESSAGE-17
#define REPAINT		MAXMESSAGE-18
#define TIMER		MAXMESSAGE-19
#define DATAUPDATE  MAXMESSAGE-20

//����������
/*���� ����������
   P |  UP   | ESC
--------------------
LEFT | ENTER | RIGHT
--------------------
  F1 | DOWN  |   F2
*/
#define kbNone    0 //������ ������� �� ������
#define kbESC     1 //������ (� ����� �� ���� ������� ���� �����)
#define kbUp      72 //2 //������� �����
#define kbP       3 //����� ����
#define kbRight   4 //������� ������
#define kbENT     13//5 //����� ������
#define kbLeft    6 //������� �����
#define kbF2      7 //�������������� ������� F2
#define kbDown    80//8 //������� ����
#define kbF1      9 //�������������� ������� F1

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