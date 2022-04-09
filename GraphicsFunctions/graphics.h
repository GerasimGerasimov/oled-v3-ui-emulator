#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <string>
#include <vector>
#include "stm32f4xx.h"

#define VIEW_PORT_MAX_WIDTH  128 //ширина
#define VIEW_PORT_MAX_HEIGHT 64  //высота

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
		static void Line(u8 X1, u8 Y1, u8 X2, u8 Y2, u8 Color);
		static void setPixel(TPixel& props);
		static void setPixel(u8 x, u8 y, u8 color);
		static void outText(std::string text, u16 x, u16 y, u16 color);
		static bool putChar(u8 Code, u16& x, u16 y, u16 color);
		static u8 screen[128][64];
};

#endif
