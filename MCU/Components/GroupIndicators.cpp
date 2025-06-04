#include "GroupIndicators.h"
#include <graphics.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cmath>
#include <Router.h>
#include "parameters.h"
#include <PageHome.h>
#include "IniResources.h"

GroupIndicators::GroupIndicators(int x, int y, u8 colorState, std::string outValue1, std::string sparksV) {
	ElementRect.Left = x;
	ElementRect.Top = y;
	ElementRect.Height = 63;
	ElementRect.Width = 29;
	this->colorState = colorState;
	objOut = (TParameter*)IniResources::getSignalByTag(outValue1);
	objSparks = (TParameter*)IniResources::getSignalByTag(sparksV);
}

void GroupIndicators::view() 
{
	TFillRect background{ ElementRect.Left, ElementRect.Top, ElementRect.Width, ElementRect.Height, abs(colorState - 0) };
	TGrahics::fillRect(background);
	TGrahics::Line(ElementRect.Left, ElementRect.Top + 28, ElementRect.Left + 26, ElementRect.Top + 28, abs(colorState - 1));
	TGrahics::Line(ElementRect.Left, ElementRect.Top + 46, ElementRect.Left + 26, ElementRect.Top + 46, abs(colorState - 1));
	TGrahics::outText("сост", ElementRect.Left + 2, ElementRect.Top + 45, abs(colorState - 1), "Verdana12");
	point();
	outValue();
	sparksValue();
	stateValue();
}
const u16 GroupIndicators::getHeight(void)
{
	return u16(ElementRect.Height);
}
void GroupIndicators::outValue()
{
	TGrahics::outText("OUT", ElementRect.Left + 1, ElementRect.Top, abs(colorState - 1), "Verdana12");
	TGrahics::outText(outValue1, ElementRect.Left + 3, ElementRect.Top + 8,abs(colorState - 1), "Verdana12");
	TGrahics::outText("%", ElementRect.Left + 6, ElementRect.Top + 14, abs(colorState - 1), "MSSansSerifBold14");
}

void GroupIndicators::sparksValue()
{
	TGrahics::outText(sparksV, ElementRect.Left + 2, ElementRect.Top + 30, abs(colorState - 1), "Verdana12");
	TGrahics::outText("иск", ElementRect.Left + 4, ElementRect.Top + 36, abs(colorState - 1), "Verdana12");
}
void GroupIndicators::stateValue()
{
	std::string sparksValue = "opa";
	
	for (int i = 0; i < sparksValue.size(); i++) {
		u16 ratio = ElementRect.Left + ((i + 1) * 6);
		TGrahics::putChar(sparksValue[i], ratio, ElementRect.Top + 52, sparksValue[i] == mode ? 1 : 0);
	}
	
}
void GroupIndicators::setStateValue(int newMode) {
	if (newMode == 0) {
		mode = 'o';
	}
	else if (newMode == 1) {
		mode = 'p';
	}
	else {
		mode = 'a';
	}
}
void GroupIndicators::point() 
{
	TGrahics::Line(ElementRect.Left + 2, ElementRect.Top + 56, ElementRect.Left + 2, ElementRect.Top + 58, 1);
	TGrahics::Line(ElementRect.Left + 3, ElementRect.Top + 56, ElementRect.Left + 3, ElementRect.Top + 58, 1);
}
void GroupIndicators::invertOut() {
	colorState = (colorState == 0) ? 1 : 0;
	TFillRect selectionArea{ ElementRect.Left , ElementRect.Top, 27, 28 };
	TGrahics::InvertArea(selectionArea);
}
void GroupIndicators::update(const TSlotHandlerArsg& args, const char* format)
{
	outValue1 = objOut->getValue(args, "");
	sparksV = objSparks->getValue(args, "");
	try {
		outVal = std::stof(outValue1);
		char s[8];
		//GIST "%.4X" преобразование числа в hex с заданным кол-вом значащих нулей
		if (outVal < 100) {
			sprintf(s, "%.1f", outVal);
		}
		else {
			sprintf(s, "%.0f", outVal);
		}
		outValue1 = s;

		setStateValue(1);
	}
	catch (...) {
		outValue1 = "**.*";
		sparksV = "**.*";
		setStateValue(2);
	}

}