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

extern void set_console(HANDLE dest_console);

struct TTextProps {
	s16 left;
	s16 top;
	u16 color;
	u16 foreground;
};

extern void outText(TTextProps& props, std::string s);

struct TFillRect {
	s16 left;
	s16 top;
	u16 width;
	u16 height;
	u16 color;
};

extern void fillRect(TFillRect& props);

#endif
