#include "OperatingMode.h"
#include "graphics.h"

OperatingMode::OperatingMode(int x, int y) {
	this->x = x;
	this->y = y;
}

void  OperatingMode::view()
{
	drawBorder(2);
	TGrahics::outText("pp", x + 2, y, 1, "Verdana12");
	TGrahics::outText("í", x + 3, y + 8, 1, "MSSansSerifBold14");
	TGrahics::outText("î", x + 3, y + 21, 1, "MSSansSerifBold14");
	TGrahics::outText("â", x + 3, y + 34, 1, "MSSansSerifBold14");
	TGrahics::outText("ò", x + 3, y + 47, 1, "MSSansSerifBold14");
	
}

const u16 OperatingMode::getHeight(void)
{
	return u16(height);
}

void OperatingMode::drawBorder(unsigned int yPosition) {
	TFillRect drawB{ x , y + 12 + (yPosition * 13), 14, 10, 1};
	TGrahics::drawBorder(drawB);
}


