#include "CurrentIndicator.h"
#include "graphics.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cmath>

CurrentIndicator::CurrentIndicator(int x, int y, std::string msu, std::string ref, u8 colorState) : fillingBar(x, y, colorState) {

	this->x = x;
	this->y = y;
	this->msu = msu;
	this->ref = ref;
	this->colorState = colorState;
}

void CurrentIndicator::view()
{
	fillingBar.setColorState(colorState);
	drawBorder(x, y);
	displayValue();
	fillingBar.view();
	changeValue("");
	fillingBar.scaleBarValue();
}

const u16 CurrentIndicator::getHeight(void)
{
	return u16(height);
}

void CurrentIndicator::drawBorder(int drawBorderX, int drawBorderY) {
	TFillRect outerBorder{ drawBorderX + 1, drawBorderY + 15, width - 20, height - 34, std::fabs(colorState - 1)};
	TGrahics::fillRect(outerBorder);
	TFillRect intBorder{ drawBorderX + 2, drawBorderY + 16, width - 22, height - 36, std::fabs(colorState - 0) };
	TGrahics::fillRect(intBorder);
	TGrahics::outTextVertical(ref, y + 23 , x , std::fabs(colorState - 1), "Verdana12");
	TGrahics::outTextVertical("1200", x + 21, y + 8, std::fabs(colorState - 1), "Verdana12");
	
}


void CurrentIndicator::displayValue() {
	TGrahics::outText(msu, x + 3, y + 2, std::fabs(colorState - 1), "Verdana12");
}
void CurrentIndicator::changeValue(std::string current) {
	TFillRect outerBorder{ x + 3, y + 50, 32, 10, std::fabs(colorState - 0) };
	TGrahics::fillRect(outerBorder);
	current = std::to_string(getValue());
	TGrahics::outText(current, x + 7, y + 50, std::fabs(colorState - 1), "Verdana12");
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

void CurrentIndicator::invertStateColor()
{
	colorState = (colorState == 1) ? 0 : 1;
	TFillRect selectionArea{ x , y, 40, 63 };
	TGrahics::InvertArea(selectionArea);
	
}
