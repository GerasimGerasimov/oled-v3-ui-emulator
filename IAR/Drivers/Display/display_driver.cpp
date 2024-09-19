#include "display_driver.h"
#include "ssd1305.h"
#include "display_dc.h"
#include <iostream>

//������������ ������� �� � � �� � ��� �������
static const u8 MAX_END_X = 127;
static const u8 MAX_END_Y = 63;

void TDisplayDriver::setDC(void) {
}
//u8 TGrahics::screen[128] [64];  //128 ����� � 64 ������ ������������� 128 �������, � ������� 8 ���� � �������
//u8 framebuffer     [8]   [128]; //��� �������� �� SPI: 8 ����� �� 128 ����  
//���, � ���� � ������� ���������� �����������! ������� ���� ������ ��� 128 ����������� ������������� ���� � �������
//������ ��� ��� �����. � ����� ����� 8 ����

//��� ��� ���������� framebuffer`a (������� ����� ����� ������� �� OLED �� SPI)
//������������ ����������� ���������������� � ��������������� ��-�� ������������ OLED

//������ ��� ����������
//write_cmd(SSD1305_CMD_SETSEGREMAP + 0x01); //Remap
void TDisplayDriver::prepareFrame(void){
  u8* f = (u8*)&framebuffer[0][0];
  for (int m = 0; m < 64; m += 8) {
    for (int j = 0; j < 128; j++) {
        *f++ = ((TGrahics::screen[j][0+m]) ? 1 << 0 : 0)
             | ((TGrahics::screen[j][1+m]) ? 1 << 1 : 0)
             | ((TGrahics::screen[j][2+m]) ? 1 << 2 : 0)
             | ((TGrahics::screen[j][3+m]) ? 1 << 3 : 0)
             | ((TGrahics::screen[j][4+m]) ? 1 << 4 : 0)
             | ((TGrahics::screen[j][5+m]) ? 1 << 5 : 0)
             | ((TGrahics::screen[j][6+m]) ? 1 << 6 : 0)
             | ((TGrahics::screen[j][7+m]) ? 1 << 7 : 0);
    }
  }
}

/*
��� ������� � ����������� � ���������������� ��� 
write_cmd(SSD1305_CMD_SETSEGREMAP + 0x00); //No Remap
void TDisplayDriver::prepareFrame(void){
  u8 a;
  u16 m = 64;
  u8* f = (u8*)&framebuffer[7][127];
  while (m) {
    m -=8;
    int j = 0;
    while (j<128) {
        a = 0;
        a |= (TGrahics::screen[j][0+m]) ? 1 << 0 : 0;
        a |= (TGrahics::screen[j][1+m]) ? 1 << 1 : 0;
        a |= (TGrahics::screen[j][2+m]) ? 1 << 2 : 0;
        a |= (TGrahics::screen[j][3+m]) ? 1 << 3 : 0;
        a |= (TGrahics::screen[j][4+m]) ? 1 << 4 : 0;
        a |= (TGrahics::screen[j][5+m]) ? 1 << 5 : 0; 
        a |= (TGrahics::screen[j][6+m]) ? 1 << 6 : 0;
        a |= (TGrahics::screen[j][7+m]) ? 1 << 7 : 0; 
        *--f = a;
        j++;
    }
  }
}*/

/*������� ������� ������*/
void TDisplayDriver::CleanScreen(void) {
  u8* f = (u8*)&framebuffer;
  for (int i = 0; i<sizeof(framebuffer); i++){
    *f++=0;
  }
}

void TDisplayDriver::out(void) {
    prepareFrame();
    ssd1305_rst_first();
    DMA_Cmd(DMA2_Stream3, DISABLE);  //TX
    DMA2->LIFCR = (uint32_t) (DMA_FLAG_FEIF3 | DMA_FLAG_DMEIF3 | DMA_FLAG_TEIF3 | DMA_FLAG_HTIF3 | DMA_FLAG_TCIF3);
    DMA2_Stream3->NDTR = 1024;
    DMA_Cmd(DMA2_Stream3, ENABLE); //TX
      
    if ( DMA2_Stream3->NDTR!=0)
     {
       while (DMA2_Stream3->NDTR);
     }
    ssd1305_rst_second();
};

