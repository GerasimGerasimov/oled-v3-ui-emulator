#include "link_led.h"

s16 LinkLED::State = -1;
u16 LinkLED::PULSE = 25;
u16 LinkLED::PAUSE = 100;
/*TODO ��� ���� ������� ��������� LINK_LED ��� ����� �������� ����� ���������
��� �����:
  ������ 0.25 ���
  ������� 1 ���
���� �����:
  ������ 0.25 ���
  ������� 0.25 ���
*/
void LinkLED::init(void){
  LED_LINK_OFF;
}

//-1 ���� ������
// 0 ��� ������
void LinkLED::setState(s16 state) {
  State = state;
}

void LinkLED::onTimer(void){
  (State == -1)
    ? (blinkErrState())
    : (blinkNoErrState());
}

void LinkLED::blinkErrState(){  
  PULSE = 10;
  PAUSE = 100;
  blink();
}

void LinkLED::blinkNoErrState(){
  LED_LINK_ON;
  //PULSE = 15;
  //PAUSE = 15;
  //blink();
}

void LinkLED::blink(void) {
  static u32 pause = 0;
  static u32 pulse = PULSE;
  static bool doPulse = true;
  static bool doPause = false;
  if (doPulse)
    (pulse)
      ? (LED_LINK_ON, pulse--)
      : (pause = PAUSE, doPulse = false, doPause = true);
  if (doPause)
    (pause)
      ? (LED_LINK_OFF, pause--)
      : (pulse = PULSE, doPulse = true, doPause = false);       
}


