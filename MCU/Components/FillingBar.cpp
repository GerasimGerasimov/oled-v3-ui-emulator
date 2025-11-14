#include "FillingBar.h"
#include <graphics.h>
#include <string>

FillingBar::FillingBar(int x, int y, u8 colorState)
{
	ElementRect.Left = x + 2;
	ElementRect.Top = y + 37;
	ElementRect.Height = 12;
	ElementRect.Width = 35;
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
	TFillRect border{ ElementRect.Left, ElementRect.Top, ElementRect.Width, ElementRect.Height, abs(colorState - 1) };
	TGrahics::drawBorder(border);
	//pointerV();
}

void FillingBar::scaleBarFoam() //эффект пивной кружки
{
	TFillRect foam{ ElementRect.Left + 29, ElementRect.Top + 2, ElementRect.Width - 30, ElementRect.Height - 3, abs(colorState - 1) };
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
	TGrahics::Line(ElementRect.Left + 28, ElementRect.Top - 1, ElementRect.Left + 28, ElementRect.Top + 13, abs(colorState - 1));
	//TGrahics::Line(ElementRect.Left + 28, ElementRect.Top, ElementRect.Left + 28, ElementRect.Top + 10, abs(colorState - 1));
	TFillRect pointLine{ ElementRect.Left + 28, ElementRect.Top + 1, 1, ElementRect.Height - 1, abs(colorState - 0) };
	TGrahics::fillCheckeredRect(pointLine);
}

void FillingBar::setValue(float newValue)
{
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

void FillingBar::setLimitValue(int newLimitValue)
{
	limitValue = newLimitValue;
}

void FillingBar::scaleBarValue() //шкала 
{
	int percent = 0;
	int xPosition = 0;

	percent = (value * 100) / limitValue;
	xPosition = 22 - (percent * 22) / 100;

	if (value == 0) {
		TFillRect fillRect{ ElementRect.Left + 2, ElementRect.Top + 2, 0, ElementRect.Height - 3, abs(colorState - 0) };
		TGrahics::fillCheckeredRect(fillRect);
	}
	else if (value > limitValue) {
		TFillRect fillRect{ ElementRect.Left + 2, ElementRect.Top + 2, ElementRect.Width - 8, ElementRect.Height - 3, abs(colorState - 1) };
		TGrahics::fillCheckeredRect(fillRect);
		scaleBarFoam();
	}
	else if (value <= limitValue && value > 0) {
		TFillRect fillRect{ ElementRect.Left + 2, ElementRect.Top + 2, ElementRect.Width - 10 - xPosition, ElementRect.Height - 3, abs(colorState - 1) };
		TGrahics::fillCheckeredRect(fillRect);
	}
}