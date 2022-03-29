#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <string>
#include <vector>
#include "stm32f4xx.h"
#include "msg.h"
#include "fonts.h"
#include <windows.h>

#define MAX_RIGHT  16  //128 ширина
#define MAX_BOTTOM 4   //64  высота

#define BASIC_COLOR  15//1
#define NEG_COLOR    2//0

struct TTextProps {
	s16 left;
	s16 top;
	u16 color;
	u16 foreground;
};

struct TPixel {
	s16 x;
	s16 y;
	u16 color;
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
		static void console_init();
		static void set_console(HANDLE dest_console);
		static HANDLE get_console();
		static void outText(TTextProps& props, std::string s);
		static void fillRect(TFillRect& props);
		static void setPixel(TPixel& props);
		static void rect();
	private:
		static HANDLE console;
		static HDC dc;
		static HBRUSH brush;
};

#endif
