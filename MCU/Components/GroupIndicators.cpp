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

GroupIndicators::GroupIndicators(int x, int y, u8 colorState, std::string outValue1, std::string test) {
	ElementRect.Left = x;
	ElementRect.Top = y;
	ElementRect.Height = 35;
	ElementRect.Width = 29;
	this->colorState = colorState;
	objOut = (TParameter*)IniResources::getSignalByTag(outValue1);
	objTest = (TParameter*)IniResources::getSignalByTag(test);
	ISignal* o = IniResources::getSignalByTag(outValue1);
	nameOut = outValue1;
}

void GroupIndicators::view() 
{
	TFillRect background{ ElementRect.Left, ElementRect.Top, ElementRect.Width, ElementRect.Height, abs(colorState - 0) };
	TGrahics::fillRect(background);
	TGrahics::Line(ElementRect.Left, ElementRect.Top + 35, ElementRect.Left + 26, ElementRect.Top + 35, abs(colorState - 1));
	TGrahics::outText("OUT", ElementRect.Left + 1, ElementRect.Top, abs(colorState - 1), "Verdana12");
	
	if (inFocus) {
		areaState();
	}
	else {
		colorState = 0;
	}
	outValue();
}
const u16 GroupIndicators::getHeight(void)
{
	return u16(ElementRect.Height);
}
void GroupIndicators::outValue()
{
	float val = inFocus ? editVal : outVal;
	char s[32];
	if (val < 100) {
		sprintf(s, "%.1f", val);
	}
	else {
		sprintf(s, "%.0f", val);
	}
	outValue1 = s;
	TGrahics::outText(outValue1, ElementRect.Left + 3, ElementRect.Top + 11, abs(colorState - 1), "Verdana12");
	TGrahics::outText("%", ElementRect.Left + 6, ElementRect.Top + 20, abs(colorState - 1), "MSSansSerifBold14");
}


void GroupIndicators::updateObj(std::string sector, const TSlotHandlerArsg& args, const char* format)
{
	if (sector == "RAM") {
		outValue1 = objOut->getValue(args, "");
		testValue = objTest->getValue(args, "");
	}
	try {
		outVal = std::stof(outValue1);
	}
	catch (...) {
		outValue1 = "**.*";
	}

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
		case (u32)KeyCodes::Up:
			if (inFocus) {
				increase((m->p2 == (u32)KeyPressFeature::AutoRepeat) ? 2 : 1);
			}
			break;
		case (u32)KeyCodes::Down:
			if (inFocus) {
				decrease((m->p2 == (u32)KeyPressFeature::AutoRepeat) ? 2 : 1);
			}

			break;
		case (u32)KeyCodes::ESC:
			if (inFocus) {
				TRouter::setTask({ false, "Home", nullptr });
				editVal = outVal;
				inFocus = false;
			}
			break;
		case (u32)KeyCodes::ENT:
			if (inFocus) {
				//TRouter::setTask({ false, "Home", nullptr });
				char s[8];
				if (editVal < 100) {
					sprintf(s, "%.1f", editVal);
				}
				else {
					sprintf(s, "%.0f", editVal);
				}
				outValue1 = s;
				sendCmd(outValue1);
				inFocus = false;
			}
			break;
		}
		return false;
	}
	}
}


void GroupIndicators::decrease(float step) {
	/*получить текущее значение Iref, вычесть из него 1A или 5А (в зависимости
	 однократное это нажатие или автоматический повтор)и передать на EFi
	значение может быть не числовое а "**.**" когда нет связи, значит
	1) получить значение 2) убедится что числовое 3) произвести над ним вычисления
	4) превратить  в строку 5) отправить */
	if (testValue == "1") {
		if ((editVal - step) <= 0) {
			editVal = 0;
		}
		else {
			editVal -= step;
		}
	}
	//sendCmd(refValue);
}

void GroupIndicators::increase(float step) {
	/*получить текущее значение Iref, вычесть из него 1A или 5А (в зависимости
	 однократное это нажатие или автоматический повтор)и передать на EFi
	значение может быть не числовое а "**.**" когда нет связи, значит
	1) получить значение 2) убедится что числовое 3) произвести над ним вычисления
	4) превратить  в строку 5) отправить */
	if (testValue == "1") {
		editVal += step;
	}
	//sendCmd(refValue);
}

void GroupIndicators::sendCmd(std::string& refValue) {
	std::string tag;
	tag = "U1/RAM/Out/";
	/*TODO осталос решить куда записывать Iref
	  Если в RAM то надо переписывать прошивку Efi так как в NormalMode сейчас задание идёт из копии Уставок в RAM
		   и поэтому во время работы задание от кнопок меняться не будет
	  Если Flash - тогда задание меняется во время работы (записываются в Копию Уставок а от туда попадает в Регулятор и отображается в RAM)
		   но при остановке, то что Юзер на задавал, будет записано в реальный Flash
	*/
	//TryCount = 1;
	cmdSendInProcess = true;
	ModbusSlave::setValue(tag, refValue, [this](Slot* slot, u8* reply) { SlotUpdate(slot, reply); });
}

void GroupIndicators::SlotUpdate(Slot* slot, u8* reply) {
	slot->Flags |= (u16)SlotStateFlags::SKIP_SLOT;
	cmdSendInProcess = false;
}

void GroupIndicators::areaState() {

		TFillRect selectionArea{ ElementRect.Left , ElementRect.Top, ElementRect.Width - 2, 9 };
		TGrahics::InvertArea(selectionArea);

}

void GroupIndicators::startEdit() {
	editVal = outVal;
	inFocus = true;
}