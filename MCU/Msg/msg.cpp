#include "msg.h"

TMessage Msg::Messages[msg_buff_size];//������� ���������

u32 msg_queue_end = 0;//����� �������
u32 msg_queue_beg = 0;//������ �������

//void key_board();//����������� ������� ������� ����������
//key_board ����������� ������� ������� ����������
//������� ��������� ���������� �� ��������, ��������� � ������� ���������
//��������� � ������� ������� � � ���
/*
void key_board (){
  static u8 key_pred = 0;
  u8 key_tmp = buttons_check ();
  if (key_tmp != key_pred) {//�������, ���� ����� ��� �� ���������
     key_pred = key_tmp;
     //������� ���������, ��� ���������� ��������� ����������
     //������ �����-�� �������.
     send_message(KEYBOARD, key_tmp, 0);
  }
}
*/

void Msg::clear_msg_queue(){//������� ������� ���������
  u32 i = msg_buff_size;
  msg_queue_end = 0;//����� �������
  msg_queue_beg = 0;//������ �������
  while (i != 0) {//�������� ������ ��� ���� ������
    i--;
    Messages[i].Event = 0;
    Messages[i].p1 = 0;
    Messages[i].p2 = 0;  
  }
}

//������� ���������
//������� send_message, ������ ����� ��������� � ����� �������
//��� ���� ����� ������� ���������� �� 1
//� ���� ������ ������������� �������� (���-�� ��������� � ������)
//������������ � "0 ��������" - � ����� ���� ������� �� ������� �� �����������
//��� �� ����� ���������� ����� ������� �����������
void Msg::send_message(u32 event, u32 p1, u32 p2){
  Messages[msg_queue_end].Event = event;
  Messages[msg_queue_end].p1 = p1;
  Messages[msg_queue_end].p2 = p2;
  msg_queue_end++;
  if (msg_queue_end >= msg_buff_size) {msg_queue_end = 0;}
}

bool Msg::get_message(TMessage* m){
  if (msg_queue_beg == msg_queue_end) {return false;};//������� �����, ���� ��������� ������ � ����� �����
  *m = Messages[msg_queue_beg]; //������� ���������� ������� � ������� ���������
  msg_queue_beg++; //�������� ����������
  if (msg_queue_beg >= msg_buff_size) {msg_queue_beg = 0;}//����������� �������
  return true;//� ������� ���-�� ����!
}