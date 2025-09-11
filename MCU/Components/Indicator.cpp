#include "Indicator.h"
#include <graphics.h>


Indicator::Indicator(int x, int y, std::string msu, std::string ref) {
	ElementRect.Left = x;
	ElementRect.Top = y;
	ElementRect.Height = 63;
	ElementRect.Width = 40;
	this->msu = msu;
	this->ref = ref;
	this->colorState = colorState; // состояние цвета
}

void Indicator::view() {
	drawBorder(ElementRect.Left, ElementRect.Top);
	if (inFocus) {
		colorState = 1;
	}
	else {
		colorState = 0;
	}
}

const u16 Indicator::getHeight(void)
{
	return u16(ElementRect.Height);
}
void Indicator::drawBorder(int drawBorderX, int drawBorderY) {

	TFillRect background{ drawBorderX, drawBorderY, ElementRect.Width, ElementRect.Height, abs(colorState - 0) };
	TGrahics::fillRect(background);
	TFillRect outerBorder{ drawBorderX + 1, drawBorderY + 15, ElementRect.Width - 20, ElementRect.Height - 33, abs(colorState - 1) };
	TGrahics::fillRect(outerBorder);
	TFillRect intBorder{ drawBorderX + 2, drawBorderY + 16, ElementRect.Width - 22, ElementRect.Height - 35, abs(colorState - 0) };
	TGrahics::fillRect(intBorder);
}
void Indicator::displayValue() //I/U ref
{
	TGrahics::outText(msu, ElementRect.Left + 3, ElementRect.Top + 2, abs(colorState - 1), "Verdana12");
}