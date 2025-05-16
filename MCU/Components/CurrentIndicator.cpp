#include "CurrentIndicator.h"
#include "graphics.h"


CurrentIndicator::CurrentIndicator(int x, int y, std::string msu) : fillingBar(x, y) {

	this->x = x;
	this->y = y;
	this->msu = msu;
}

void CurrentIndicator::view()
{
	drawBorder(x, y);
	displayValue();
	fillingBar.view();
	changeValue("1700");
}

const u16 CurrentIndicator::getHeight(void)
{
	return u16(height);
}

void CurrentIndicator::drawBorder(int drawBorderX, int drawBorderY) {
	TFillRect outerBorder{ drawBorderX + 1, drawBorderY + 17, width - 22, height - 35, 1 };
	TGrahics::fillRect(outerBorder);
	TFillRect intBorder{ drawBorderX + 2, drawBorderY + 18, width - 24, height - 37, 0 };
	TGrahics::fillRect(intBorder);
}

void CurrentIndicator::displayValue() {
	TGrahics::outText(msu, x + 3, y + 2, 1, "Verdana12");
}
void CurrentIndicator::changeValue(std::string current) {
	TGrahics::outText(current, x + 5, y + 50, 1, "Verdana12");
}
