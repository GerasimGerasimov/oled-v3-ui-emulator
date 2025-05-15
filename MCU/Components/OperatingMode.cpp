#include "OperatingMode.h"
#include "graphics.h"

OperatingMode::OperatingMode(int x, int y) {
	this->x = x;
	this->y = y;
}

void  OperatingMode::view()
{
	drawBorder(2, 2);
	drawBorder(2, 15);
	drawBorder(2, 28);
	drawBorder(2, 41);
	TGrahics::outText("pp", x + 3, y, 1, "Verdana12");
	TGrahics::outText("í", x + 4, y + 8, 1, "MSSansSerifBold14");
	TGrahics::outText("î", x + 4, y + 21, 1, "MSSansSerifBold14");
	TGrahics::outText("â", x + 4, y + 34, 1, "MSSansSerifBold14");
	TGrahics::outText("ò", x + 4, y + 47, 1, "MSSansSerifBold14");
	
}

const u16 OperatingMode::getHeight(void)
{
	return u16(height);
}

void OperatingMode::drawBorder(int x, int y) {
	TFillRect outerBorder{ x + 84, y + 10, width - 3, height - 52, 1 };
	TGrahics::fillRect(outerBorder);
	TFillRect intBorder{ x + 85, y + 11, width - 5, height - 54, 0 };
	TGrahics::fillRect(intBorder);
}