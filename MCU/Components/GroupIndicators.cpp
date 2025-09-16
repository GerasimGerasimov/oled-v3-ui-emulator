#include "GroupIndicators.h"
#include "graphics.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cmath>
#include "Router.h"
#include "parameters.h"
#include "PageHome.h"
#include "IniResources.h"
#include <string>
#include "AppModbusSlave.h"
#include "Slot.h"
#include "TagLineTime.h"
#include "LabelTime.h"

#include <iomanip>
#include <sstream>

#define MIN_IN_HOUR 60

GroupIndicators::GroupIndicators(int x, int y, u8 colorState, std::string mode,std::string tRun, std::string wRun) {
	ElementRect.Left = x;
	ElementRect.Top = y;
	ElementRect.Height = 63;
	ElementRect.Width = 47;
	this->colorState = colorState;
	this->mode = mode;
	objRun = (TParameter*)IniResources::getSignalByTag(tRun);
	objWRun = (TParameter*)IniResources::getSignalByTag(wRun);
	ISignal* t = IniResources::getSignalByTag(tRun);
	ISignal* w = IniResources::getSignalByTag(wRun);
	container[0] = t;
	container[1] = w;

}

void GroupIndicators::view() {
	TFillRect background{ ElementRect.Left, ElementRect.Top, ElementRect.Width, ElementRect.Height, abs(colorState - 0) };
	TGrahics::fillRect(background);
	TGrahics::Line(ElementRect.Left, ElementRect.Top + 20, ElementRect.Left + ElementRect.Width, ElementRect.Top + 20, abs(colorState - 1));
	TGrahics::Line(ElementRect.Left, ElementRect.Top + 41, ElementRect.Left + ElementRect.Width, ElementRect.Top + 41, abs(colorState - 1));
	TGrahics::outText("Режим", ElementRect.Left + 2, ElementRect.Top , abs(colorState - 1), "Verdana12");
	TGrahics::outText("Время", ElementRect.Left + 2, ElementRect.Top + 21, abs(colorState - 1), "Verdana12");
	TGrahics::outText("Мощн.", ElementRect.Left + 2, ElementRect.Top + 42, abs(colorState - 1), "Verdana12");

	valueMode();

	if (inFocus) {
		areaState(yPos);
	}
	else {
		colorState = 0;
	}
}

const u16 GroupIndicators::getHeight(void)
{
	return u16(ElementRect.Height);
}

void GroupIndicators::valueMode() {
	TGrahics::outText(mode, ElementRect.Left + 1, ElementRect.Top + 10, abs(colorState - 1), "Verdana12");
	TGrahics::outText("1000", ElementRect.Left + 1, ElementRect.Top + 31, abs(colorState - 1), "Verdana12");
	TGrahics::outText("1000", ElementRect.Left + 2, ElementRect.Top + 52, abs(colorState - 1), "Verdana12");
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
		case (u32)KeyCodes::ESC:
			if (inFocus) {
				TRouter::setTask({ false, "Home", nullptr });
			}
			break;
		case (u32)KeyCodes::F1:
			if (inFocus) {
				TRouter::setTask({ false, "Help", container[component] });
			}
			break;
		case (u32)KeyCodes::Up:
			if (inFocus) {
				if (component > 0 && component <= 2) {
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
				if (component < 2 && component >= 0) {
					component++;
					yPos++;
				}
				else {
					component = 2;
					yPos = 2;
				}
				areaState(yPos);
			}
			break;
		}

		return false;
	}
	}
}
void GroupIndicators::areaState(unsigned int yPos) {
	//editStateValue();
	if (yPos == 0) {
		TFillRect selectionArea{ ElementRect.Left , ElementRect.Top, ElementRect.Width, 9 };
		TGrahics::InvertArea(selectionArea);
	}
	else  if (yPos == 1) {
		TFillRect selectionArea{ ElementRect.Left, ElementRect.Top + 21, ElementRect.Width, 10 };
		TGrahics::InvertArea(selectionArea);
	}
	else if (yPos == 2) {
		TFillRect selectionArea{ ElementRect.Left, ElementRect.Top + 42, ElementRect.Width, 9 };
		TGrahics::InvertArea(selectionArea);
	}

}