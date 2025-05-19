#include "CurrentIndicator.h"
#include "graphics.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

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
	fillingBar.scaleBarValue();
}

const u16 CurrentIndicator::getHeight(void)
{
	return u16(height);
}

void CurrentIndicator::drawBorder(int drawBorderX, int drawBorderY) {
	TFillRect outerBorder{ drawBorderX + 1, drawBorderY + 15, width - 20, height - 34, 1 };
	TGrahics::fillRect(outerBorder);
	TFillRect intBorder{ drawBorderX + 2, drawBorderY + 16, width - 22, height - 36, 0 };
	TGrahics::fillRect(intBorder);

	TGrahics::outTextVertical("Iref", x + 24, y - 1 , 1, "Verdana12");
	TGrahics::outTextVertical("1200", x + 21, y + 8, 1, "Verdana12");
}

void CurrentIndicator::displayValue() {
	TGrahics::outText(msu, x + 3, y + 2, 1, "Verdana12");
}
void CurrentIndicator::changeValue(std::string current) {
	TFillRect outerBorder{ x + 3, y + 50, 32, 10, 0 };
	TGrahics::fillRect(outerBorder);
	current = std::to_string(getValue());
	TGrahics::outText(current, x + 7, y + 50, 1, "Verdana12");
}

void CurrentIndicator::invertArea() {
	TFillRect selectionArea{ x, y, 40, 63 };
	TGrahics::InvertArea(selectionArea);
}

void CurrentIndicator::setValue(int newValue)
{
	fillingBar.setValue(newValue);
}

int CurrentIndicator::getValue()
{
	return fillingBar.getValue();
}
