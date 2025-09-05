#include "OperatingMode.h"
#include "graphics.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cmath>
#include "Router.h"
#include "parameters.h"
#include "PageHome.h"
#include "IniResources.h"
#include "AppModbusSlave.h"

OperatingMode::OperatingMode(int x, int y, u8 colorState, std::string normal, std::string clean, std::string vac, std::string manual) {
	ElementRect.Left = x;
	ElementRect.Top = y;
	ElementRect.Height = 65;
	ElementRect.Width = 17;
	this->colorState = colorState;
	objNormal = (TParameter*)IniResources::getSignalByTag(normal);
	objClean = (TParameter*)IniResources::getSignalByTag(clean);
	objVac = (TParameter*)IniResources::getSignalByTag(vac);
	objManual = (TParameter*)IniResources::getSignalByTag(manual);
	ISignal* n = IniResources::getSignalByTag(normal);
	ISignal* c = IniResources::getSignalByTag(clean);
	ISignal* v = IniResources::getSignalByTag(vac);
	ISignal* m = IniResources::getSignalByTag(manual);
	container[0] = n;
	container[1] = c;
	container[2] = v;
	container[3] = m;
	SubscriberID = HandlerSubscribers::set("U1/RAM/", [this](TSlotHandlerArsg args) { SlotUpdateRAM(args); });
}

void  OperatingMode::view()
{
	background();
	drawBorder();
	hidingBorder();
	
	TGrahics::outText("pp", ElementRect.Left + 2, ElementRect.Top, abs(colorState - 1), "Verdana12");
	TGrahics::outText("í", ElementRect.Left + 4, ElementRect.Top + 8, abs(colorState - 1), "MSSansSerifBold14");
	TGrahics::outText("î", ElementRect.Left + 4, ElementRect.Top + 21, abs(colorState - 1), "MSSansSerifBold14");
	TGrahics::outText("â", ElementRect.Left + 4, ElementRect.Top + 34, abs(colorState - 1), "MSSansSerifBold14");
	TGrahics::outText("ò", ElementRect.Left + 4, ElementRect.Top + 47, abs(colorState - 1), "MSSansSerifBold14");

	//TGrahics::outText(cleanValue, ElementRect.Left + 4, ElementRect.Top + 47, abs(colorState - 1), "MSSansSerifBold14");
	if (inFocus) {
		colorState = 1;
		//SubscriberID = HandlerSubscribers::set("U1/RAM/", [this](TSlotHandlerArsg args) { SlotUpdateRAM(args); });
		//HandlerSubscribers::remove("U1/RAM/", SubscriberID);
	}
	else {
		colorState = 0;
		setYPosition();
	}
}

const u16 OperatingMode::getHeight(void)
{
	return u16(ElementRect.Height);
}

void OperatingMode::background() {
	TFillRect drawBorder{ ElementRect.Left, ElementRect.Top, ElementRect.Width -1, ElementRect.Height, abs(colorState - 0) };
	TGrahics::fillRect(drawBorder);
}

void OperatingMode::drawBorder() {
	TFillRect drawBorder{ ElementRect.Left + 1, ElementRect.Top + 12 + (yPosition * 13), 13, 10, abs(colorState - 1)};
	TGrahics::drawBorder(drawBorder);
}
void OperatingMode::stateValue(u8 newColor)
{
	colorState = (colorState == 0) ? 1 : 0;
	TFillRect selectionArea{ ElementRect.Left , ElementRect.Top, ElementRect.Width, ElementRect.Height };
	TGrahics::InvertArea(selectionArea);
}
int OperatingMode::getYPosition()
{
	return yPosition;
}

void OperatingMode::hidingBorder() {
	TFillRect drawB{ ElementRect.Top + 83, ElementRect.Left - 20 + (yPosition * 13), 13, 10, abs(colorState - 0) };
	TGrahics::drawBorder(drawB);
}

bool OperatingMode::ProcessMessage(TMessage* m)
{
	switch (m->Event) {
	case (u32)EventSrc::KEYBOARD: {
		switch (m->p1) {
		case (u32)KeyCodes::Up:
			if (inFocus) {
				if (yPosition > 0 && yPosition <= 3) {
					yPosition -= 1;
				}
				else {
					yPosition = 0;
				}
				if (component > 0 && component <= 3) {
					component--;
				}
				else {
					component = 0;
				}
				sendModeCmd(container[component]);
			}
			break;
		case (u32)KeyCodes::Down:
			if (inFocus) {
				//HandlerSubscribers::remove("U1/RAM/", SubscriberID);
				if (yPosition < 3 && yPosition >= 0) {
					yPosition += 1;
				}
				else {
					yPosition = 3;
				}
				if (component < 3 && component >= 0) {
					component++;
				}
				else {
					component = 3;
				}
				sendModeCmd(container[component]);
			}
			break;
		case (u32)KeyCodes::F1:
			if (inFocus) {
				if (yPosition == 0) {
					TRouter::setTask({ false, "Help", container[0] });
				}
				else if (yPosition == 1) {
					TRouter::setTask({ false, "Help", container[1] });
				}
				else if (yPosition == 2) {
					TRouter::setTask({ false, "Help", container[2] });
				}
				else  { 
					TRouter::setTask({ false, "Help", container[3] });
				}
			}
			break;
		case (u32)KeyCodes::ESC:
			if (inFocus) {
				TRouter::setTask({ false, "Home", nullptr });
			}
			break;
		}
		for (auto& element : List) {
			element->ProcessMessage(m);
		}
		return false;
	}
	}
}
void OperatingMode::updateObj(std::string sector, const TSlotHandlerArsg& args, const char* format)
{
	if (sector == "RAM") {
		normalValue = objNormal->getValue(args, ""); //sendModeCmd(container[1]);
		cleanValue = objClean->getValue(args, "");
		vacValue = objVac->getValue(args, "");
		manualValue = objManual->getValue(args, "");
	}
	//if (inFocus == false) {
	//	/*setYPosition();*/
	//}
	//else {
	//	colorState = 1;
	//	//setYPosition();
	//}
}

void OperatingMode::setYPosition()  
{
	if (normalValue == "1") {
		yPosition = 0;
	}
	else if (cleanValue == "1") {
		yPosition = 1;
	}
	else if (vacValue == "1") {
		yPosition = 2;
	}
	else if (manualValue == "1") {
		yPosition = 3;
	}
	else {
		TFillRect drawBorder{ ElementRect.Left + 1, ElementRect.Top + 12 + (yPosition * 13), 13, 10, abs(colorState - 0) };
		TGrahics::drawBorder(drawBorder);
	}
	
	
}

static const std::string CMD_NORMAL = "5310";
static const std::string CMD_CLEAN = "5311";
static const std::string CMD_VAC = "5312";
static const std::string CMD_TEST = "5313";

static const std::map <std::string, std::string> CmdBySignalName = {
	{"Normal", CMD_NORMAL},
	{"Clean", CMD_CLEAN},
	{"VAC", CMD_VAC},
	{"Manual", CMD_TEST}
};

void OperatingMode::sendModeCmd(ISignal* signal) {
	std::string name = signal->getName();
	if (CmdBySignalName.count(name)) {
		sendCmd((std::string&)CmdBySignalName.at(name));
	}
	//normalValue = (std::string&)CmdBySignalName.at(name);
}

void OperatingMode::sendCmd(std::string& code) {
	std::string cmd = "U1/RAM/CMD/";
	TryCount = 3;
	cmdSendInProcess = true;
	ModbusSlave::setValue(cmd, code, [this](Slot* slot, u8* reply) { SlotUpdate(slot, reply); });
}

void OperatingMode::SlotUpdate(Slot* slot, u8* reply) {
	if (slot->RespondLenghtOrErrorCode) {
		slot->Flags |= (u16)SlotStateFlags::SKIP_SLOT;
		cmdSendInProcess = false;
	}
	else {
		if (TryCount)
			TryCount--;
		else {
			slot->Flags |= (u16)SlotStateFlags::SKIP_SLOT;
			cmdSendInProcess = false;
		}
	}
}

void OperatingMode::SlotUpdate(const char* sector, TSlotHandlerArsg args) {
	updateObj(sector, args, "");

	Msg::send_message((u32)EventSrc::REPAINT, 0, 0);
}

void OperatingMode::SlotUpdateRAM(TSlotHandlerArsg args) {
	SlotUpdate("RAM", args);
}