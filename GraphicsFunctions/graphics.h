#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <string>
#include <vector>
#include "stm32f4xx.h"
#include "msg.h"
//#include "fonts.h"

#define VIEW_PORT_MAX_WIDTH  128 //������
#define VIEW_PORT_MAX_HEIGHT 64  //������

struct TTextProps {
	s16 left;
	s16 top;
	u16 color;
	u16 foreground;
};

struct TPixel {
	s16 x;
	s16 y;
	u8 color;
};

struct TFillRect {
	s16 left;
	s16 top;
	u16 width;
	u16 height;
	u16 color;
};

struct TGrahics {
	public:
		static void setPixel(TPixel& props);
		static u8 screen[128][64];
};

#endif
