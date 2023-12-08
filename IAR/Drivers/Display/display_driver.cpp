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

void TDisplayDriver::prepareFrame(void){
  u8 a;
  u8 m = 0;
  u8* f = &framebuffer[0][0];
  for (int i=0; i<8; i++) {
    for (int j=0; j<128; j++) {
        a = 0;
        a |= (TGrahics::screen[j][0+m]) ? 1 << 0 : 0;
        a |= (TGrahics::screen[j][1+m]) ? 1 << 1 : 0;
        a |= (TGrahics::screen[j][2+m]) ? 1 << 2 : 0;
        a |= (TGrahics::screen[j][3+m]) ? 1 << 3 : 0;
        a |= (TGrahics::screen[j][4+m]) ? 1 << 4 : 0;
        a |= (TGrahics::screen[j][5+m]) ? 1 << 5 : 0; 
        a |= (TGrahics::screen[j][6+m]) ? 1 << 6 : 0;
        a |= (TGrahics::screen[j][7+m]) ? 1 << 7 : 0; 
        *f++ = a;
    }
    m +=8;
  }
}

/*
const static u8 Mask[] = {1, 2, 4, 8, 16, 32, 64, 128};
 
void TDisplayDriver::prepareFrame(void){
  u8 p = 0;
  u8* f = &framebuffer[0];
  for (int x = 0; x < 128; x++) {
    for (int y = 0; y < 64; y++) {
      p = TGrahics::screen[x][y];
      u16 PixNum = (y<<7)+x; //����� ������� � ���������� �������, ��� ����������� ��� Y*128 + X
      u16 ByteNum = PixNum >> 3;;//����� ����� � ���������� �������  ��� ����������� ��� PixNum/8
      u8 BitMask = Mask[PixNum -  (ByteNum << 3)];//����� ��� ����
      u8* a = f+ByteNum;
      (p)
        ?(*a |=  BitMask)
        :(*a &= ~BitMask);
    }
  }
}
*/

/*������� ������� ������*/
void TDisplayDriver::CleanScreen(void) {
  u8* f = &framebuffer[0][0];
  for (int i = 0; i<sizeof(framebuffer); i++){
    *f++=0;
  }
}

/*������� ���������� ������*/
void TDisplayDriver::rotateFrame(void){
  static u8 framebuffer_tmp[8][128];
  
  //����������� ������ �� ���������
  u32* ft = (u32*)&framebuffer_tmp;
  u32* fs = (u32*)&framebuffer;
  for (int i=0; i<(2*128); i++){
    *ft++ = *fs++;
  }
  
  //�������������� ������� � �����
  for (int i=0; i<8; i++) {
    for (int j=0; j<(MAX_END_X+1); j++) {
      framebuffer[i][j]=framebuffer_tmp[i][MAX_END_X - j];
    }
  }
}

void TDisplayDriver::out(void) {
    prepareFrame();
    rotateFrame();
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

