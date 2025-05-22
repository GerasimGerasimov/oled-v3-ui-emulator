#include "CurrentIndicator.h"
#include "graphics.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cmath>
#include <Router.h>
#include "parameters.h"
#include <PageHome.h>

CurrentIndicator::CurrentIndicator(int x, int y, std::string msu, std::string ref, std::string read, u8 colorState, int limitValue, int maxValue, float ratio) : fillingBar(x, y, colorState, limitValue, maxValue) {
	ElementRect.Left = x;
	ElementRect.Top = y;
	ElementRect.Height = 63;
	ElementRect.Width = 40;
	this->msu = msu;
	this->ref = ref;
	this->read = read;
	this->colorState = colorState;
	this->limitValue = limitValue;
	this->maxValue = maxValue;
	this->ratio = ratio;
}

void CurrentIndicator::view()
{
	fillingBar.setColorState(colorState);
	drawBorder(ElementRect.Left, ElementRect.Top);
	displayValue();
	fillingBar.view();
	changeValue("");
	fillingBar.scaleBarValue();
	if (inFocus) {
		colorState = 1;
	}
	else {
		colorState = 0;
	}
}

const u16 CurrentIndicator::getHeight(void)
{
	return u16(ElementRect.Height);
}

void CurrentIndicator::drawBorder(int drawBorderX, int drawBorderY) {

	TFillRect background{ drawBorderX, drawBorderY, ElementRect.Width, ElementRect.Height, std::fabs(colorState - 0) };
	TGrahics::fillRect(background);
	TFillRect outerBorder{ drawBorderX + 1, drawBorderY + 15, ElementRect.Width - 20, ElementRect.Height - 34, std::fabs(colorState - 1)};
	TGrahics::fillRect(outerBorder);
	TFillRect intBorder{ drawBorderX + 2, drawBorderY + 16, ElementRect.Width - 22, ElementRect.Height - 36, std::fabs(colorState - 0) };
	TGrahics::fillRect(intBorder);
	TGrahics::outTextVertical(ref, ElementRect.Top + 23 , ElementRect.Left , std::fabs(colorState - 1), "Verdana12");
	TGrahics::outTextVertical(read, ElementRect.Top + 21, ElementRect.Left + 8, std::fabs(colorState - 1), "Verdana12");
	
}

void CurrentIndicator::displayValue() {
	TGrahics::outText(msu, ElementRect.Left + 3, ElementRect.Top + 2, std::fabs(colorState - 1), "Verdana12");
}

void CurrentIndicator::changeValue(std::string current) {

	if (fillingBar.getValue() > limitValue) {
		TFillRect outerBorder{ ElementRect.Left + 6, ElementRect.Top + 50, 30, 9, 1 };
		TGrahics::fillRect(outerBorder);
		char s[8];
		//GIST "%.4X" преобразование числа в hex с заданным кол-вом значащих нулей
		if (fillingBar.getValue() < 100) {
			sprintf(s, "%.1f", getValue());
		}
		else {
			sprintf(s, "%.0f", getValue());
		}
		current = s;
		TGrahics::outText(current, ElementRect.Left + 7, ElementRect.Top + 50, 0, "Verdana12");
	}
	else {
		TFillRect outerBorder{ ElementRect.Left + 6, ElementRect.Top + 50, 30, 9, 0 };
		TGrahics::fillRect(outerBorder);
		//current = std::to_string(getValue());
		char s[8];
		//GIST "%.4X" преобразование числа в hex с заданным кол-вом значащих нулей
		if (fillingBar.getValue() < 100) {
			sprintf(s, "%.1f", getValue());
		}
		else {
			sprintf(s, "%.0f", getValue());
		}
		current = s;
		TGrahics::outText( current, ElementRect.Left + 7, ElementRect.Top + 50, 1, "Verdana12");
	}
}


void CurrentIndicator::invertArea() {

	TFillRect selectionArea{ ElementRect.Left, ElementRect.Top, ElementRect.Width, ElementRect.Height };
	TGrahics::InvertArea(selectionArea);
}

void CurrentIndicator::setValue(float newValue)
{
	fillingBar.setValue(newValue);
}

float CurrentIndicator::getValue()
{
	return fillingBar.getValue();
}

void CurrentIndicator::invertStateColor()
{
	//colorState = (colorState == 1) ? 0 : 1;
	TFillRect selectionArea{ ElementRect.Left, ElementRect.Top, 40, 63 };
	TGrahics::InvertArea(selectionArea);
	
}
void CurrentIndicator::scaleBar()
{
	fillingBar.scaleBarValue();
}
bool CurrentIndicator::ProcessMessage(TMessage* m)
{
	switch (m->Event) {
	case (u32)EventSrc::KEYBOARD: {
		switch (m->p1) {
		case (u32)KeyCodes::Up:
			if (inFocus) {
				setValue(getValue() + 85 * ratio);
			}
			break;
		case (u32)KeyCodes::Down:
			if (inFocus) {
				setValue(getValue() - 85 * ratio);
			}
			
			break;
		}
	}
	for (auto& element : List) {
		element->ProcessMessage(m);
	}
	return false;
	}
}