#include "FlashData.h"//�������� �������� �������� ������

TFLASH_DATA FLASH_DATA =
{     
    0x00000401, //Modbus_RS485;  u32  0-1-2-3
    0x00000401, //Lnkmngr_RS485;u32 4-5-6-7
    100,   //TIME_OUT_Lnkmngr u16 8-9
    50,     //TIME_CHANGE_Lnkmngr u16 a-b
    1.0f, // Koef_null  float 4 ����� c-d-e-f
    //������������ 
    {
      1,//integer 10-11-12-13
      0.1f, //FracDecScale 14-15-16-17
      0.01f,//FracHundScale 18-19-1a-1b
      0.001f,//sTshake 1c-1d-1e-1f
      0.0001f,// FracDecThousScale 20-21-22-23
      0, //24-27
      0, //28-2b
      0, //2c-2f
      0, //30-33
      0, //34-37
      0, //38-3b
      0, //3c-3f
      0, //40-43
      0, //44-47
      0, //48-4b
      0, //4c-4f
      0, //50-53
      0, //54-57
      0, //58-5b
      0  //5c-5f
    },  
   0,  //60 Password  
   0,   //62 Retranslate; 
   0x0002,
   2,
   //0,
 
}; 