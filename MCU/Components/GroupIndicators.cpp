#include "GroupIndicators.h"
#include <graphics.h>
#include <iostream>
#include <cmath>

GroupIndicators::GroupIndicators(int x, int y, u8 colorState) {
	ElementRect.Left = x;
	ElementRect.Top = y;
	ElementRect.Height = 63;
	ElementRect.Width = 29;
	this->colorState = colorState;
}

void GroupIndicators::view() 
{
	TFillRect background{ ElementRect.Left, ElementRect.Top, ElementRect.Width, ElementRect.Height, std::fabs(colorState - 0) };
	TGrahics::fillRect(background);
	TGrahics::Line(ElementRect.Left, ElementRect.Top + 28, ElementRect.Left + 26, ElementRect.Top + 28, std::fabs(colorState - 1));
	TGrahics::Line(ElementRect.Left, ElementRect.Top + 46, ElementRect.Left + 26, ElementRect.Top + 46, std::fabs(colorState - 1));
	outValue("100");
	sparksValue("200");
	stateValue('p');
}
const u16 GroupIndicators::getHeight(void)
{
	return u16(ElementRect.Height);
}
void GroupIndicators::outValue(std::string outValue)
{
	TGrahics::outText("OUT", ElementRect.Left + 1, ElementRect.Top, std::fabs(colorState - 1), "Verdana12");
	TGrahics::outText(outValue, ElementRect.Left + 2, ElementRect.Top + 8, std::fabs(colorState - 1), "Verdana12");
	TGrahics::outText("%", ElementRect.Left + 6, ElementRect.Top + 14, std::fabs(colorState - 1), "MSSansSerifBold14");
}

void GroupIndicators::sparksValue(std::string sparksValue)
{
	TGrahics::outText(sparksValue, ElementRect.Left + 2, ElementRect.Top + 29, std::fabs(colorState - 1), "Verdana12");
	TGrahics::outText("иск", ElementRect.Left + 4, ElementRect.Top + 36, std::fabs(colorState - 1), "Verdana12");
}
void GroupIndicators::stateValue(char mode)
{
	std::string sparksValue = "opa";
	TGrahics::outText("сост", ElementRect.Left + 2, ElementRect.Top + 45, std::fabs(colorState - 1), "Verdana12");
	
	for (int i = 0; i < sparksValue.size(); i++) {
		u16 ratio = ElementRect.Left + ((i + 1) * 6);
		TGrahics::putChar(sparksValue[i], ratio, ElementRect.Top + 52, sparksValue[i] == mode ? 1 : 0);
	}
	point();
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