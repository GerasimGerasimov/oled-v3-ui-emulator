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
	TGrahics::Line(ElementRect.Left, ElementRect.Top + 20, ElementRect.Left + ElementRect.Width, ElementRect.Top + 20, abs(colorState - 1));
	TGrahics::Line(ElementRect.Left, ElementRect.Top + 41, ElementRect.Left + ElementRect.Width, ElementRect.Top + 41, abs(colorState - 1));
	TGrahics::outText("Режим", ElementRect.Left + 2, ElementRect.Top , abs(colorState - 1), "Verdana12");
	TGrahics::outText("Время", ElementRect.Left + 2, ElementRect.Top + 21, abs(colorState - 1), "Verdana12");
	TGrahics::outText("Мощн.", ElementRect.Left + 2, ElementRect.Top + 42, abs(colorState - 1), "Verdana12");

	valueMode();
}

const u16 GroupIndicators::getHeight(void)
{
	return u16(ElementRect.Height);
}

void GroupIndicators::valueMode() {
	TGrahics::outText(mode, ElementRect.Left + 1, ElementRect.Top + 10, abs(colorState - 1), "Verdana12");
	TGrahics::outText("tRunValue", ElementRect.Left + 1, ElementRect.Top + 31, abs(colorState - 1), "Verdana12");
	TGrahics::outText("BCharge", ElementRect.Left + 2, ElementRect.Top + 52, abs(colorState - 1), "Verdana12");
}