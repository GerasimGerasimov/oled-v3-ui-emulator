#include "graphics.h"
#include <iostream>

u8 TGrahics::screen[128][64];

void TGrahics::setPixel(TPixel& props) {
	screen[props.x][props.y] = props.color;
}