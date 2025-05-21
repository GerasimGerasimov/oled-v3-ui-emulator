#include "CurrentIndicator.h"
#include "graphics.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cmath>
#include <Router.h>
#include "parameters.h"
#include <PageHome.h>

CurrentIndicator::CurrentIndicator(int x, int y, std::string msu, std::string ref, u8 colorState) : fillingBar(x, y, colorState) {
	ElementRect.Left = x;
	ElementRect.Top = y;
	ElementRect.Height = 63;
	ElementRect.Width = 40;
	this->msu = msu;
	this->ref = ref;
	this->colorState = colorState;
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
	TGrahics::outTextVertical("1200", ElementRect.Left + 21, ElementRect.Top + 8, std::fabs(colorState - 1), "Verdana12");
	
}

void CurrentIndicator::displayValue() {
	TGrahics::outText(msu, ElementRect.Left + 3, ElementRect.Top + 2, std::fabs(colorState - 1), "Verdana12");
}

void CurrentIndicator::changeValue(std::string current) {
	TFillRect outerBorder{ ElementRect.Left + 3, ElementRect.Top + 50, 32, 10, 0 };
	TGrahics::fillRect(outerBorder);
	current = std::to_string(getValue());
	TGrahics::outText(current, ElementRect.Left + 7, ElementRect.Top + 50, 1, "Verdana12");
}

void CurrentIndicator::invertArea() {

	TFillRect selectionArea{ ElementRect.Left, ElementRect.Top, ElementRect.Width, ElementRect.Height };
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
				setValue(getValue() + 85);
			}
			break;
		case (u32)KeyCodes::Down:
			if (inFocus) {
				setValue(getValue() - 85);
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