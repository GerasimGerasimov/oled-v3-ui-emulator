#include "GroupIndicators.h"
#include <graphics.h>

GroupIndicators::GroupIndicators(int x, int y) {
	this->x = x;
	this->y = y;
}

void GroupIndicators::view() 
{
	TGrahics::Line(x, y + 28, x + 26, y + 28, 1);
	TGrahics::Line(x, y + 46, x + 26, y + 46, 1);
	outValue("100");
	sparksValue("200");
	stateValue('o');
}
const u16 GroupIndicators::getHeight(void)
{
	return u16(height);
}
void GroupIndicators::outValue(std::string outValue)
{
	TGrahics::outText("OUT", x + 1, y, 1, "Verdana12");
	TGrahics::outText(outValue, x + 2, y + 8, 1, "Verdana12");
	TGrahics::outText("%", x + 6, y + 14, 1, "MSSansSerifBold14");
}

void GroupIndicators::sparksValue(std::string sparksValue)
{
	TGrahics::outText(sparksValue, x + 2, y + 29, 1, "Verdana12");
	TGrahics::outText("иск", x + 4, y + 36, 1, "Verdana12");
}
void GroupIndicators::stateValue(char mode)
{
	std::string sparksValue = "opa";
	TGrahics::outText("сост", x + 2, y + 45, 1, "Verdana12");
	
	for (int i = 0; i < sparksValue.size(); i++) {
		u16 ratio = x + ((i + 1) * 6);
		TGrahics::putChar(sparksValue[i], ratio, y + 52, sparksValue[i] == mode ? 1 : 0);
	}
	
	point();
}
void GroupIndicators::point() 
{
	TGrahics::Line(x + 2, y + 56, x + 2, y + 58, 1);
	TGrahics::Line(x + 3, y + 56, x + 3, y + 58, 1);
}
