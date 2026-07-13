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
#include <AppModbusSlave.h>

#include <iomanip>
#include <sstream>

#define MIN_IN_HOUR 60

GroupIndicators::GroupIndicators(int x, int y, u8 colorState, std::string tRun) {
	ElementRect.Left = x;
	ElementRect.Top = y;
	ElementRect.Height = 63;
	ElementRect.Width = 46;
	this->colorState = colorState;
	objOut = (TParameter*)IniResources::getSignalByTag(tRun);
	ISignal* o = IniResources::getSignalByTag(tRun);
	nameOut = tRun;
}

void GroupIndicators::view() 
{
	TFillRect background{ ElementRect.Left, ElementRect.Top, ElementRect.Width, ElementRect.Height, abs(colorState - 0) };
	TGrahics::fillRect(background);
	//TGrahics::Line(ElementRect.Left, ElementRect.Top + 35, ElementRect.Left + ElementRect.Width, ElementRect.Top + 35, abs(colorState - 1));

	TGrahics::outText("¬рем€", ElementRect.Left + 1, ElementRect.Top + 2, abs(colorState - 1), "Verdana12");

	tValue();

	if (inFocus) {
		//areaState();
		colorState = 1;
	}
	else {
		colorState = 0;
	}
	
}
const u16 GroupIndicators::getHeight(void)
{
	return u16(ElementRect.Height);
}
void GroupIndicators::tValue()
{
	TGrahics::outText(tRunValue, ElementRect.Left + 1, ElementRect.Top + 15, abs(colorState - 1), "Verdana12");
}


void GroupIndicators::updateObj(std::string sector, const TSlotHandlerArsg& args, const char* format)
{
	if (sector == "RAM") {
		tRunValue = objOut->getValue(args, "");
		
	}
	try {
		if (tRunValue != newTime) {
			if (tRunValue != (static_cast<TParameter*>(objOut)->getDefaultValue())) {
				timeValue();
			}
		}
	}
	catch (...) {
		tRunValue = "**.*";
	}

}

void GroupIndicators::timeValue() {
	int time;
	std::stringstream stream(tRunValue);
	u16 hour, minut;
	stream >> time;
	hour = time / MIN_IN_HOUR;
	minut = time % MIN_IN_HOUR;

	stream.seekg(0);
	stream.str("");
	if (hour <= 99) {
		stream << std::setfill('0') << std::setw(2) << hour << 'ч' << std::setfill('0') << std::setw(2) << minut << 'м';
	}
	else {
		stream << std::setfill('0') << std::setw(2) << hour << 'ч';
	}
	stream >> tRunValue;
	newTime = tRunValue;

}

bool GroupIndicators::ProcessMessage(TMessage* m) {
	switch (m->Event) {
	case (u32)EventSrc::KEYBOARD: {
		switch (m->p1) {
		case (u32)KeyCodes::F1:
			if (inFocus) {
				ISignal* p = IniResources::getSignalByTag(nameOut);
				TRouter::setTask({ false, "Help", p });
			}
			break;

		case (u32)KeyCodes::ESC:
			if (inFocus) {
				TRouter::setTask({ false, "Home", nullptr });
			}
			break;
		case (u32)KeyCodes::ENT:
			if (inFocus) {
				//TRouter::setTask({ false, "Home", nullptr });
				inFocus = false;
			}
			break;
		}
		return false;
	}
	}
}


void GroupIndicators::startEdit() {
	//editVal = outVal;
	inFocus = true;
}