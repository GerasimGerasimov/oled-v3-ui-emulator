#include "GroupIndicators.h"
#include <graphics.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cmath>
#include "Router.h"
#include "parameters.h"
#include "PageHome.h"
#include "IniResources.h"

GroupIndicators::GroupIndicators(int x, int y, u8 colorState, std::string outValue1, std::string sparksV, std::string ready, std::string run) {
	ElementRect.Left = x;
	ElementRect.Top = y;
	ElementRect.Height = 64;
	ElementRect.Width = 29;
	this->colorState = colorState;
	objOut = (TParameter*)IniResources::getSignalByTag(outValue1);
	objSparks = (TParameter*)IniResources::getSignalByTag(sparksV);
	objReady = (TParameter*)IniResources::getSignalByTag(ready);
	objRun = (TParameter*)IniResources::getSignalByTag(run);
	ISignal* o = IniResources::getSignalByTag(outValue1);
	ISignal* s = IniResources::getSignalByTag(sparksV);
	ISignal* r = IniResources::getSignalByTag(ready);
	ISignal* n = IniResources::getSignalByTag(run);
	container[0] = o;
	container[1] = s;
	container[2] = r;
	container[3] = n;
}

void GroupIndicators::view() 
{
	TFillRect background{ ElementRect.Left, ElementRect.Top, ElementRect.Width, ElementRect.Height, abs(colorState - 0) };
	TGrahics::fillRect(background);
	TGrahics::Line(ElementRect.Left, ElementRect.Top + 28, ElementRect.Left + 26, ElementRect.Top + 28, abs(colorState - 1));
	TGrahics::Line(ElementRect.Left, ElementRect.Top + 46, ElementRect.Left + 26, ElementRect.Top + 46, abs(colorState - 1));
	TGrahics::outText("OUT", ElementRect.Left + 1, ElementRect.Top, abs(colorState - 1), "Verdana12");
	TGrahics::outText("иск", ElementRect.Left + 4, ElementRect.Top + 27, abs(colorState - 1), "Verdana12");
	TGrahics::outText("сост", ElementRect.Left + 2, ElementRect.Top + 45, abs(colorState - 1), "Verdana12");
	if (inFocus) {
		areaState(yPos);
	}
	else {
		colorState = 0;
		stateValue();
		setStateValue();
	}
	point();
	outValue();
	sparksValue();
	//stateValue();
}
const u16 GroupIndicators::getHeight(void)
{
	return u16(ElementRect.Height);
}
void GroupIndicators::outValue()
{
	
	char s[8];
	//GIST "%.4X" преобразование числа в hex с заданным кол-вом значащих нулей
	if (outVal < 100) {
		sprintf(s, "%.1f", outVal);
	}
	else {
		sprintf(s, "%.0f", outVal);
	}
	outValue1 = s;
	TGrahics::outText(outValue1, ElementRect.Left + 3, ElementRect.Top + 8,abs(colorState - 1), "Verdana12");
	TGrahics::outText("%", ElementRect.Left + 6, ElementRect.Top + 14, abs(colorState - 1), "MSSansSerifBold14");
}
void GroupIndicators::sparksValue()
{
	TGrahics::outText(sparksV, ElementRect.Left + 2, ElementRect.Top + 36, abs(colorState - 1), "Verdana12");
}
void GroupIndicators::stateValue()
{
	std::string sparksValue = "opa";
	for (int i = 0; i < sparksValue.size(); i++) {
		u16 ratio = ElementRect.Left + ((i + 1) * 6);
		TGrahics::putChar(sparksValue[i], ratio, ElementRect.Top + 52, sparksValue[i] == mode ? 1 : 0);
	}

}
void GroupIndicators::editStateValue() {
	std::string sparksValue = "opa";
	TGrahics::outText(sparksValue, ElementRect.Left + 6, ElementRect.Top + 52, abs(colorState - 1), "Verdana12");
}
void GroupIndicators::setStateValue() {
	 if (runValue == "1") {
		mode = 'p';
	}
	else if (readyValue == "1") {
		mode = 'o';
	}
	else {
		mode = 'a';
	}
}
void GroupIndicators::point() 
{
	TGrahics::Line(ElementRect.Left + 2, ElementRect.Top + 56, ElementRect.Left + 2, ElementRect.Top + 59, 1);
	TGrahics::Line(ElementRect.Left + 3, ElementRect.Top + 56, ElementRect.Left + 3, ElementRect.Top + 59, 1);
	TGrahics::Line(ElementRect.Left + 1, ElementRect.Top + 57, ElementRect.Left + 4, ElementRect.Top + 57, 1);
	TGrahics::Line(ElementRect.Left + 1, ElementRect.Top + 58, ElementRect.Left + 4, ElementRect.Top + 58, 1);

}
void GroupIndicators::updateObj(std::string sector, const TSlotHandlerArsg& args, const char* format)
{
	if (sector == "RAM") {
		outValue1 = objOut->getValue(args, "");
		sparksV = objSparks->getValue(args, "");
		readyValue = objReady->getValue(args, "");
		runValue = objRun->getValue(args, "");
	}
	try {
		outVal = std::stof(outValue1);
	}
	catch (...) {
		outValue1 = "**.*";
		sparksV = "**.*";
		mode = 'a';
	}

}

bool GroupIndicators::ProcessMessage(TMessage* m) {
	switch (m->Event) {
	case (u32)EventSrc::KEYBOARD: {
		switch (m->p1) {
		case (u32)KeyCodes::F1:
			if (inFocus) {
				TRouter::setTask({ false, "Help", container[component] });
			}
			break;
		case (u32)KeyCodes::Up:
			if (inFocus) {
				if (component > 0 && component <= 3) {
					component--;
					yPos--;
				}
				else {
					component = 0;
					yPos = 0;
				}
				areaState(yPos);
			}
			break;
		case (u32)KeyCodes::Down:
			if (inFocus) {
				if(component < 3 && component >= 0) {
					component++;
					yPos++;
				}
				else {
					component = 3;
					yPos = 3;
				}
				areaState(yPos);
			}
			break;
		case (u32)KeyCodes::ESC:
			if (inFocus) {
				TRouter::setTask({ false, "Home", nullptr });
			}
			break;
		}
		return false;
	}
	}
}
void GroupIndicators::areaState(unsigned int yPos) {
	editStateValue();
	if (yPos == 0) {
		TFillRect selectionArea{ ElementRect.Left , ElementRect.Top, ElementRect.Width - 2, 9 };
		TGrahics::InvertArea(selectionArea);
	}
	else  if (yPos == 1) {
		TFillRect selectionArea{ ElementRect.Left, ElementRect.Top + 29, ElementRect.Width - 2, 7};
		TGrahics::InvertArea(selectionArea);
	}
	else if (yPos == 2) {
		TFillRect selectionArea{ ElementRect.Left, ElementRect.Top + 47, ElementRect.Width - 2, 7};
		TGrahics::InvertArea(selectionArea);
		TFillRect selState{ ElementRect.Left + 6, ElementRect.Top + 54, ElementRect.Width - 23, 8 };
		TGrahics::InvertArea(selState);
	}
	else if (yPos == 3) {
		TFillRect selectionArea{ ElementRect.Left, ElementRect.Top + 47, ElementRect.Width - 2, 7 };
		TGrahics::InvertArea(selectionArea);
		TFillRect selState{ ElementRect.Left + 12, ElementRect.Top + 54, ElementRect.Width - 22, 8 };
		TGrahics::InvertArea(selState);
	}
	
}