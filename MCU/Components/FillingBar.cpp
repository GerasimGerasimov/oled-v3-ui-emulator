#include "FillingBar.h"
#include <graphics.h>
FillingBar::FillingBar(int x, int y, u8 colorState)
{
	ElementRect.Left = x + 27;
	ElementRect.Top = y + 16;
	ElementRect.Height = 28;
	ElementRect.Width = 12;
	this->colorState = colorState;
	this->value = value;
}

void FillingBar::view()
{
	drawBorder();
	drawThreshold();
}

const u16 FillingBar::getHeight(void)
{
	return u16(ElementRect.Height);
}

void FillingBar::drawBorder()
{
	TFillRect outerBorder{ ElementRect.Left, ElementRect.Top, ElementRect.Width, ElementRect.Height, abs(colorState - 1) };
	TGrahics::fillRect(outerBorder);
	TFillRect intBorder{ ElementRect.Left + 2, ElementRect.Top + 1, ElementRect.Width - 3, ElementRect.Height - 1, abs(colorState - 0) };
	TGrahics::fillRect(intBorder);
	pointerV();
}

void FillingBar::scaleBarFoam() //эффект пивной кружки
{
	TFillRect foam{ ElementRect.Left + 3, ElementRect.Top + 2, ElementRect.Width - 5, ElementRect.Height - 24, abs(colorState - 1) };
	TGrahics::fillRect(foam);
}

void FillingBar::pointerV() //стрелка вертикальная
{
	TGrahics::Line(ElementRect.Left + 6, ElementRect.Top + 29, ElementRect.Left + 8, ElementRect.Top + 31, abs(colorState - 1));
	TGrahics::Line(ElementRect.Left + 6, ElementRect.Top + 30, ElementRect.Left + 8, ElementRect.Top + 32, abs(colorState - 1));
	TGrahics::Line(ElementRect.Left + 6, ElementRect.Top + 29, ElementRect.Left + 4, ElementRect.Top + 31, abs(colorState - 1));
	TGrahics::Line(ElementRect.Left + 6, ElementRect.Top + 30, ElementRect.Left + 4, ElementRect.Top + 32, abs(colorState - 1));
}

void FillingBar::drawThreshold() //линия порогового значения шкалы
{
	TGrahics::Line(ElementRect.Left - 2, ElementRect.Top + 6, ElementRect.Left + 12, ElementRect.Top + 6, abs(colorState - 1));
	TGrahics::Line(ElementRect.Left + 2, ElementRect.Top + 6, ElementRect.Left + 10, ElementRect.Top + 6, abs(colorState - 0));
	TFillRect pointLine{ ElementRect.Left + 2, ElementRect.Top + 6, ElementRect.Width - 3, ElementRect.Height - 27, abs(colorState - 0) };
	//TGrahics::fillCheckeredRect(pointLine);
}

void FillingBar::setValue(float newValue)
{
	if (newValue > maxValueInt) {
		newValue = maxValueInt;
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

void FillingBar::setMaxValue(int newMaxValue)
{
	maxValueInt = newMaxValue;
}
int FillingBar::getMaxValue()
{
	//return currentIndicator.getMaxValue();
	return maxValueInt;
}
void FillingBar::setLimitValue(int newLimitValue)
{
	limitValue = newLimitValue;
}

void FillingBar::scaleBarValue() //шкала 
{
	int percent = 0;
	int yPosition = 0;
	percent = (value * 100) / limitValue;
	yPosition = 22 - (percent * 22) / 100;

	if (value == 0) {
		TFillRect fillRect{ ElementRect.Left + 3, ElementRect.Top + 28, ElementRect.Width - 5, ElementRect.Height - 28, abs(colorState - 1) };
		//TGrahics::fillCheckeredRect(fillRect);
	}
	else if (value <= limitValue && value > 0) {
		TFillRect fillRect{ ElementRect.Left + 3, ElementRect.Top + yPosition + 5, ElementRect.Width - 5, ElementRect.Height - 5 - yPosition, abs(colorState - 1) };
		//TGrahics::fillCheckeredRect(fillRect);
	}
	else if (value > limitValue) {
		TFillRect fillRect{ ElementRect.Left + 3, ElementRect.Top + 5, ElementRect.Width - 5, ElementRect.Height - 5, abs(colorState - 1) };
		//TGrahics::fillCheckeredRect(fillRect);
		scaleBarFoam();
	}

}