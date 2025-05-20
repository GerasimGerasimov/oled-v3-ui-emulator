#include "FillingBar.h"
#include "graphics.h"
#include <iostream>
#include <cmath>

FillingBar::FillingBar(int x, int y, u8 colorState)
{
	this->x = x + 26;
	this->y = y + 16;
	this->colorState = colorState;
}

void FillingBar::view()
{
	drawBorder();
	pointerH(10);
	drawThreshold();
}

const u16 FillingBar::getHeight(void)
{
	return u16(height);
}

void FillingBar::drawBorder()
{
	
	TFillRect outerBorder{ x, y, width, height, std::fabs(colorState - 1) };
	TGrahics::fillRect(outerBorder);
	TFillRect intBorder{ x + 2, y + 1, width-3, height-1, std::fabs(colorState - 0) };
	TGrahics::fillRect(intBorder);
	TFillRect pointLine{ x + 3, y + 6, width - 5, height - 27, std::fabs(colorState - 1) };
	TGrahics::fillCheckeredRect(pointLine);
	pointerV();
}

void FillingBar::scaleBarFoam() 
{
	TFillRect foam{ x + 3, y + 2, width - 5, height - 24, std::fabs(colorState - 1) };
	TGrahics::fillRect(foam);
	
}

void FillingBar::scaleBarValue()
{
int percent = 0; 
int yPosition = 0;
percent = (value * 100) / maxValue;
yPosition = 25 - (percent * 25) / 100;
if (value < limitValue) {
	TFillRect fillRect{ x + 3, y + yPosition + 3, width - 5, height - 3 - yPosition, std::fabs(colorState - 1) };
	TGrahics::fillCheckeredRect(fillRect);
	}
else if (value >= limitValue && value <= maxValue) {
	TFillRect fillRect{ x + 3, y + yPosition + 3, width - 5, height - 3 - yPosition, std::fabs(colorState - 1) };
	TGrahics::fillCheckeredRect(fillRect);
	scaleBarFoam();
}

}

void FillingBar::pointerH(unsigned int yPosition)
{
	TGrahics::Line(x - 2, y + 2 + yPosition, x - 4, y + yPosition, std::fabs(colorState - 1));
	TGrahics::Line(x - 3, y + 2 + yPosition, x - 5, y + yPosition, std::fabs(colorState - 1));
	TGrahics::Line(x - 2, y + 2 + yPosition, x - 4, y + 4 + yPosition, std::fabs(colorState - 1));
	TGrahics::Line(x - 3, y + 2 + yPosition, x - 5, y + 4 + yPosition, std::fabs(colorState - 1));
	TGrahics::Line(x + 1, y + 2 + yPosition, x + 2, y + 2 + yPosition, std::fabs(colorState - 0));
}

void FillingBar::pointerV() 
{
	TGrahics::Line(x + 6, y + 29, x + 8, y + 31, std::fabs(colorState - 1));
	TGrahics::Line(x + 6, y + 30, x + 8, y + 32, std::fabs(colorState - 1));
	TGrahics::Line(x + 6, y + 29, x + 4, y + 31, std::fabs(colorState - 1));
	TGrahics::Line(x + 6, y + 30, x + 4, y + 32, std::fabs(colorState - 1));
}

void FillingBar::drawThreshold() 
{
	TGrahics::Line(x - 2, y + 6, x + 12, y + 6, std::fabs(colorState - 1));
	TGrahics::Line(x + 2, y + 6, x + 10, y + 6, std::fabs(colorState - 0));
	TFillRect pointLine{ x + 3, y + 6, width - 5, height - 27, std::fabs(colorState - 1) };
	TGrahics::fillCheckeredRect(pointLine);
}

void FillingBar::setValue(int newValue)
{
	if (newValue > maxValue) {
		newValue = maxValue;
	}
	else if (newValue < 0) {
		newValue = 0;
	}

	value = newValue;
}

int FillingBar::getValue()
{
	return value;
}
void FillingBar::setColorState(u8 newColor)
{
	colorState = newColor;
}