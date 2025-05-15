#include "FillingBar.h"
#include "graphics.h"

FillingBar::FillingBar(int x, int y)
{
	this->x = x + 26;
	this->y = y + 16;
}

void FillingBar::view()
{
	drawBorder();
	scaleBarValue();
}

const u16 FillingBar::getHeight(void)
{
	return u16(height);
}

void FillingBar::drawBorder()
{
	TFillRect outerBorder{ x, y, width, height, 1 };
	TGrahics::fillRect(outerBorder);
	TFillRect intBorder{ x + 2, y + 1, width-3, height-1, 0 };
	TGrahics::fillRect(intBorder);
}

void FillingBar::scaleBar() {
	TGrahics::Line(x - 2, y + 5, x + 12, y + 5, 1);
	TGrahics::Line(x + 2, y + 5, x + 10, y + 5, 0);
	TFillRect topBar{ x + 3, y + 2, width - 5, height - 15, 1 };
	TGrahics::fillRect(topBar);
	TFillRect fillRect{ x + 3, y + 5, width - 5, height - 5, 1 };
	TGrahics::fillCheckeredRect(fillRect);
	pointerH(10);
	pointerV();
}

void FillingBar::scaleBarValue() {
	/*TGrahics::Line(x - 2, y + 5, x + 12, y + 5, 1);
	TGrahics::Line(x + 2, y + 5, x + 10, y + 5, 0);
	TFillRect topBar{ x + 3, y + 2, width - 5, height - 15, 1 };
	TGrahics::fillRect(topBar);*/
	TFillRect fillRect{ x + 3, y + 8, width - 5, height - 8, 1 };
	TGrahics::fillCheckeredRect(fillRect);
	pointerH(10);
	pointerV();
}

void FillingBar::pointerH(unsigned int yPosition) {
	TGrahics::Line(x - 2, y + 2 + yPosition, x - 4, y + yPosition, 1);
	TGrahics::Line(x - 3, y + 2 + yPosition, x - 5, y + yPosition, 1);
	TGrahics::Line(x - 2, y + 2 + yPosition, x - 4, y + 4 + yPosition, 1);
	TGrahics::Line(x - 3, y + 2 + yPosition, x - 5, y + 4 + yPosition, 1);
	TGrahics::Line(x + 1, y + 2 + yPosition, x + 2, y + 2 + yPosition, 0);
}

void FillingBar::pointerV() {
	TGrahics::Line(x + 6, y + 29, x + 8, y + 31, 1);
	TGrahics::Line(x + 6, y + 30, x + 8, y + 32, 1);
	TGrahics::Line(x + 6, y + 29, x + 4, y + 31, 1);
	TGrahics::Line(x + 6, y + 30, x + 4, y + 32, 1);
}