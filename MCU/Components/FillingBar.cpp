#include "FillingBar.h"
#include "graphics.h"
#include <iostream>
#include <cmath>

FillingBar::FillingBar(int x, int y, u8 colorState, int limitValue, int maxValue, float value)
{
	ElementRect.Left = x + 27;
	ElementRect.Top = y + 16;
	ElementRect.Height = 28;
	ElementRect.Width = 12;
	this->colorState = colorState;
	this->limitValue = limitValue;
	this->maxValue = maxValue;
	this->value = value;
}

void FillingBar::view()
{
	drawBorder();
	//pointerH(7);
	drawThreshold();
}

const u16 FillingBar::getHeight(void)
{
	return u16(ElementRect.Height);
}

void FillingBar::drawBorder()
{
	TFillRect outerBorder{ ElementRect.Left, ElementRect.Top, ElementRect.Width, ElementRect.Height, std::fabs(colorState - 1) };
	TGrahics::fillRect(outerBorder);
	TFillRect intBorder{ ElementRect.Left + 2, ElementRect.Top + 1, ElementRect.Width - 3, ElementRect.Height - 1, std::fabs(colorState - 0) };
	TGrahics::fillRect(intBorder);
	TFillRect pointLine{ ElementRect.Left + 3, ElementRect.Top + 6, ElementRect.Width - 5, ElementRect.Height - 27, std::fabs(colorState - 1) };
	TGrahics::fillCheckeredRect(pointLine);
	pointerV();
}

void FillingBar::scaleBarFoam() //эффект пивной кружки
{
	TFillRect foam{ ElementRect.Left + 3, ElementRect.Top + 2, ElementRect.Width - 5, ElementRect.Height - 24, std::fabs(colorState - 1) };
	TGrahics::fillRect(foam);
}

void FillingBar::scaleBarValue() //шкала 
{
	int percent = 0; 
	int yPosition = 0;
	percent = (value * 100) / maxValue;
	yPosition = 25 - (percent * 25) / 100;

	if (value < limitValue) {
		TFillRect fillRect{ ElementRect.Left + 3, ElementRect.Top + yPosition + 3, ElementRect.Width - 5, ElementRect.Height - 3 - yPosition, std::fabs(colorState - 1) };
		TGrahics::fillCheckeredRect(fillRect);
		}
	else if (value >= limitValue && value <= maxValue) {
		TFillRect fillRect{ ElementRect.Left + 3, ElementRect.Top + yPosition + 2, ElementRect.Width - 5, ElementRect.Height - 2 - yPosition, std::fabs(colorState - 1) };
		TGrahics::fillCheckeredRect(fillRect);
		scaleBarFoam();
	}
}

//void FillingBar::pointerH(unsigned int yPosition) //стрелка горизонтальная
//{
//	TGrahics::Line(ElementRect.Left - 2, ElementRect.Top + 2 + yPosition, ElementRect.Left - 4, ElementRect.Top + yPosition, std::fabs(colorState - 1));
//	TGrahics::Line(ElementRect.Left - 3, ElementRect.Top + 2 + yPosition, ElementRect.Left - 5, ElementRect.Top + yPosition, std::fabs(colorState - 1));
//	TGrahics::Line(ElementRect.Left - 2, ElementRect.Top + 2 + yPosition, ElementRect.Left - 4, ElementRect.Top + 4 + yPosition, std::fabs(colorState - 1));
//	TGrahics::Line(ElementRect.Left - 3, ElementRect.Top + 2 + yPosition, ElementRect.Left - 5, ElementRect.Top + 4 + yPosition, std::fabs(colorState - 1));
//	TGrahics::Line(ElementRect.Left + 1, ElementRect.Top + 2 + yPosition, ElementRect.Left + 2, ElementRect.Top + 2 + yPosition, std::fabs(colorState - 0));
//}

void FillingBar::pointerV() //стрелка вертикальная
{
	TGrahics::Line(ElementRect.Left + 6, ElementRect.Top + 29, ElementRect.Left + 8, ElementRect.Top + 31, std::fabs(colorState - 1));
	TGrahics::Line(ElementRect.Left + 6, ElementRect.Top + 30, ElementRect.Left + 8, ElementRect.Top + 32, std::fabs(colorState - 1));
	TGrahics::Line(ElementRect.Left + 6, ElementRect.Top + 29, ElementRect.Left + 4, ElementRect.Top + 31, std::fabs(colorState - 1));
	TGrahics::Line(ElementRect.Left + 6, ElementRect.Top + 30, ElementRect.Left + 4, ElementRect.Top + 32, std::fabs(colorState - 1));
}

void FillingBar::drawThreshold() 
{
	TGrahics::Line(ElementRect.Left - 2, ElementRect.Top + 6, ElementRect.Left + 12, ElementRect.Top + 6, std::fabs(colorState - 1));
	TGrahics::Line(ElementRect.Left + 2, ElementRect.Top + 6, ElementRect.Left + 10, ElementRect.Top + 6, std::fabs(colorState - 0));
	TFillRect pointLine{ ElementRect.Left + 3, ElementRect.Top + 6, ElementRect.Width - 5, ElementRect.Height - 27, std::fabs(colorState - 1) };
	TGrahics::fillCheckeredRect(pointLine);
}

void FillingBar::setValue(float newValue)
{
	if (newValue > maxValue) {
		newValue = maxValue;
	}
	else if (newValue < 0) {
		newValue = 0;
	}
	value = newValue;
}

float FillingBar::getValue()
{
	return value;
}
void FillingBar::setColorState(u8 newColor)
{
	colorState = newColor;
}