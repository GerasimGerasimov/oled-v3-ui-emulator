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

GroupIndicators::GroupIndicators(int x, int y, u8 colorState, std::string outValue1) {
	ElementRect.Left = x;
	ElementRect.Top = y;
	ElementRect.Height = 31;
	ElementRect.Width = 46;
	this->colorState = colorState;
	objOut = (TParameter*)IniResources::getSignalByTag(outValue1);
	ISignal* o = IniResources::getSignalByTag(outValue1);
	nameOut = outValue1;
}

void GroupIndicators::view() 
{
	TFillRect background{ ElementRect.Left, ElementRect.Top, ElementRect.Width, ElementRect.Height, abs(colorState - 0) };
	TGrahics::fillRect(background);
	//TGrahics::Line(ElementRect.Left, ElementRect.Top + 35, ElementRect.Left + ElementRect.Width, ElementRect.Top + 35, abs(colorState - 1));

	TGrahics::outText("t, min", ElementRect.Left + 4, ElementRect.Top + 2, abs(colorState - 1), "Verdana12");
	
	if (inFocus) {
		//areaState();
		colorState = 1;
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
	if (outVal < 100) {
		sprintf(s, "%.1f", outVal);
	}
	else {
		sprintf(s, "%.0f", outVal);
	}
	outValue1 = s;
	TGrahics::outText(outValue1, ElementRect.Left + 3, ElementRect.Top + 15, abs(colorState - 1), "Verdana12");
}


void GroupIndicators::updateObj(std::string sector, const TSlotHandlerArsg& args, const char* format)
{
	if (sector == "RAM") {
		outValue1 = objOut->getValue(args, "");
		
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


//void GroupIndicators::decrease(float step) {
//	/*получить текущее значение Iref, вычесть из него 1A или 5А (в зависимости
//	 однократное это нажатие или автоматический повтор)и передать на EFi
//	значение может быть не числовое а "**.**" когда нет связи, значит
//	1) получить значение 2) убедится что числовое 3) произвести над ним вычисления
//	4) превратить  в строку 5) отправить */
//	/*if (testValue == "1") {
//		if ((editVal - step) <= 0) {
//			editVal = 0;
//		}
//		else {
//			editVal -= step;
//		}
//	}*/
//	//sendCmd(refValue);
//}

//void GroupIndicators::increase(float step) {
//	/*получить текущее значение Iref, вычесть из него 1A или 5А (в зависимости
//	 однократное это нажатие или автоматический повтор)и передать на EFi
//	значение может быть не числовое а "**.**" когда нет связи, значит
//	1) получить значение 2) убедится что числовое 3) произвести над ним вычисления
//	4) превратить  в строку 5) отправить */
//	/*if (testValue == "1") {
//		editVal += step;
//	}*/
//	//sendCmd(refValue);
//}

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
	//editVal = outVal;
	inFocus = true;
}