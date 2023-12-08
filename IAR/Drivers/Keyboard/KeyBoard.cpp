#include "KeyBoard.h"
#include "msg.h"
#include "RAMdata.h"

static const u8 BTN_CNT_MAX = 10; //1 = �� ������� ��� ����� ��������� ������� ������ ��� ���������� �������� ���������

enum class KeyCtrl : u32 {
        ROW1 = GPIO_Pin_0,
        ROW2 = GPIO_Pin_1,
        ROW3 = GPIO_Pin_2,
        COL1 = GPIO_Pin_13,
        COL2 = GPIO_Pin_14,
        COL3 = GPIO_Pin_15,
        COLUMNS = 0xe000,
        COLUMNS_OFS = 0x07, 
        ROWS = 0x07
};

enum class KeyRepeatCtrl {
  First,
  Next
};

u16 KeyBoard::ScanCode = 0;
u16 KeyBoard::repeatState = (u16)KeyRepeatCtrl::First;
u16 KeyBoard::repeatDelay = 0;

void KeyBoard::sendKeyboardMsg(void) {
  static u16 prevScanCode = 0;
    if (ScanCode != prevScanCode) {
      Msg::send_message((u32)EventSrc::KEYBOARD, ScanCode, 0);
      prevScanCode = ScanCode;
      prepareToRepeat();
    } else {
      if (ScanCode) {
        repeating();
      }
    }
}

static const u16 FirstDelay = 650;
static const u16 NextDelay = 150;

void KeyBoard::prepareToRepeat(void){
  repeatState = (u16)KeyRepeatCtrl::First;
  repeatDelay = FirstDelay;
}

void KeyBoard::repeating(void){
  switch (repeatState) {
    case (u16)KeyRepeatCtrl::First:
        (repeatDelay)
          ? repeatDelay --
          : (repeatState = (u16)KeyRepeatCtrl::Next);
      break;
    case (u16)KeyRepeatCtrl::Next:
        (repeatDelay)
          ? repeatDelay --
          : ( repeatDelay = NextDelay,
                Msg::send_message((u32)EventSrc::KEYBOARD, ScanCode, 0),
                 0);    
    break;
  }
}

u16 KeyBoard::getScanCode(void) //������� �������� - ������ �� ������ � ���� �� - �� �����
{ 
  u16 delay_cnt;
  u8 row1=0, row2=0,row3=0;// �������� ������
  u16 col=0;// �������� �������
  u16 btn=0;// ����� ������� ������
  
    GPIOC->ODR ^= (u32)KeyCtrl::ROW1; //  ������ 0 �� ������ ������
    delay_cnt = 0xff; //���������
    while(delay_cnt--);
    col= GPIOB->IDR & (u32)KeyCtrl::COLUMNS;    //  ������� ������ �������� GPIOC
    row1 = ((~(col>>13)) & (u32)KeyCtrl::COLUMNS_OFS); // �������� ��� ������ ������ ������ 3
    GPIOC->ODR |= (u32)KeyCtrl::ROWS; // ��������� ��� ������
    
    GPIOC->ODR ^= (u32)KeyCtrl::ROW2; //  ������ 0 �� ������ ������
    delay_cnt = 0xff; //���������
    while(delay_cnt--);
    col= GPIOB->IDR & (u32)KeyCtrl::COLUMNS;    //  ������� ������ �������� GPIOC
    row2 = ((~(col>>13)) & (u32)KeyCtrl::COLUMNS_OFS); // �������� ��� ������ ������ ������ 3
    GPIOC->ODR |= (u32)KeyCtrl::ROWS; // ��������� ��� ������
    
    GPIOC->ODR ^= (u32)KeyCtrl::ROW3; //  ������ 0 �� ������ ������
    delay_cnt = 0xff; //���������
    while(delay_cnt--);
    col= GPIOB->IDR & (u32)KeyCtrl::COLUMNS;    //  ������� ������ �������� GPIOC
    row3 = ((~(col>>13)) & (u32)KeyCtrl::COLUMNS_OFS); // �������� ��� ������ ������� ������ 3
    
    GPIOC->ODR |= (u32)KeyCtrl::ROWS; // ��������� ��� ������

    btn = row1 + (row2 << 3) + (row3 << 6);

    return btn; // ������� ������ ������� ������
}


/*������� ��������� ���� ������� ������ � ����������� ��������*/
void KeyBoard::debouncing(u16 rawcode)
{
  static u16 btn_cur=0;
  static u16 btn_last=0;
  static u8 btn_cnt=0;
  
  if (rawcode ==0)ScanCode = 0; //��� ������ - ���������� ���� ���� ��� � ������
  
  if (btn_cnt == 0) //������ ������� �������� ��������
  {
    if (rawcode != btn_cur) //������ ������� ������, ������ ���
    {
      btn_cnt++; //������ ������ �������� �� �������
      btn_cur = rawcode; //��������� ��������� �������� ������� ������
    }    
  }
  else //�������� �� ������� ��� ����
  {
    if (rawcode==btn_cur) btn_cnt++; //��� ��� ������ �� ������
    else 
    {
      btn_cnt=0; //������ �� ������ - ���������� �������� �� �������     
    }
  }
  
  if(btn_cnt > BTN_CNT_MAX) //���� ��������� �� ������� �������-�� ����������
  {
    btn_cnt = 1; //�������� ���� � 1, �� ������ ��� �� ������
    if (btn_cur == btn_last) //���� ������ ������ �� ��, ��� � ����������
    {
        ScanCode = btn_cur; //� ������ �������� ���� ������ ������ - �� ��������� ��������
    }
    else //���� ��������� ������� ������ ���� ������
    { 
      if (ScanCode==0) //���� �� ���� ������� ������ 
      {
        ScanCode = btn_cur; //1<<(btn_cur -1);  //�������, ��� ������ ������ ���� ��� �����-��
        btn_last = btn_cur; //��������� �� �������� 
      }
      else btn_last=0; //��������� � ���������� �������� = 0
    }
  }
  RAM_DATA.var2 = ScanCode;
}



