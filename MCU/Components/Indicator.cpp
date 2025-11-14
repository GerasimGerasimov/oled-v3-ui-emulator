#include "Indicator.h"
#include <graphics.h>
#include "Router.h"
#include "parameters.h"
#include "PageHome.h"
#include "IniResources.h"
#include <string>
#include "AppModbusSlave.h"
#include "Slot.h"


Indicator::Indicator(int x, int y, std::string msu, std::string ref, std::string valueOut, std::string valueRef, std::string valueMax, std::string valueMin, std::string step, std::string valueOutMax) : fillingBar(x, y, colorState) {
	ElementRect.Left = x;
	ElementRect.Top = y;
	ElementRect.Height = 63;
	ElementRect.Width = 40;
	this->msu = msu;
	this->ref = ref;
	this->colorState = colorState; // состояние цвета

	objValueRef = (TParameter*)IniResources::getSignalByTag(valueRef);
	objValueOut = (TParameter*)IniResources::getSignalByTag(valueOut);
	objValueRefMax = (TParameter*)IniResources::getSignalByTag(valueMax);
	objValueRefMin = (TParameter*)IniResources::getSignalByTag(valueMin);
	objStep = (TParameter*)IniResources::getSignalByTag(step);
	objValueOutMax = (TParameter*)IniResources::getSignalByTag(valueOutMax);
	nameValue = valueRef;
	nameRef = valueRef;
}

void Indicator::view() {
	drawBorder(ElementRect.Left, ElementRect.Top);
	if (inFocus) {
		colorState = 1;
	}
	else {
		colorState = 0;
	}
	fillingBar.setColorState(colorState);
	fillingBar.view();
	displayValue();
	valueRef();
	fillingBar.scaleBarValue();
	pointerH();

}

const u16 Indicator::getHeight(void)
{
	return u16(ElementRect.Height);
}
void Indicator::drawBorder(int drawBorderX, int drawBorderY) {

	TFillRect background{ drawBorderX, drawBorderY, ElementRect.Width, ElementRect.Height, abs(colorState - 0) };
	TGrahics::fillRect(background);
	TFillRect outerBorder{ drawBorderX + 1, drawBorderY + 15, ElementRect.Width - 20, ElementRect.Height - 33, abs(colorState - 1) };
	TGrahics::fillRect(outerBorder);
	TFillRect intBorder{ drawBorderX + 2, drawBorderY + 16, ElementRect.Width - 22, ElementRect.Height - 35, abs(colorState - 0) };
	TGrahics::fillRect(intBorder);
}
void Indicator::displayValue() //I/U ref
{
	TGrahics::outText(msu, ElementRect.Left + 1, ElementRect.Top + 2, abs(colorState - 1), "Verdana12");
	if (valueOutF > valueOutMaxInt) {
		TFillRect outerBorder{ ElementRect.Left + 4, ElementRect.Top + 50, 34, 9, abs(colorState - 1) };
		TGrahics::fillRect(outerBorder);
		char s[8];
		if (valueOutF < 100) {
			sprintf(s, "%.1f", valueOutF);
		}
		else {
			sprintf(s, "%.0f", valueOutF);
		}
		valueOut = s;
		TGrahics::outText(valueOut, ElementRect.Left + 7, ElementRect.Top + 50, abs(colorState - 0), "Verdana12");
	}
	else {
		TFillRect outerBorder{ ElementRect.Left + 4, ElementRect.Top + 50, 34, 9, 0 };
		//TGrahics::fillRect(outerBorder);
		if (valueOut != "**.*") {
			TGrahics::outText(valueOut, ElementRect.Left + 7, ElementRect.Top + 50, abs(colorState - 1), "Verdana12");
		}
		TGrahics::outText(valueOut, ElementRect.Left + 7, ElementRect.Top + 50, abs(colorState - 1), "Verdana12");
	}

	/*fillingBar.setValue(valuePoint);
	limValueInt = 100;
	fillingBar.setLimitValue(limValueInt);*/
}

void Indicator::valueRef() //значение ref
{
	char s[8];
	if (valueRefF < 100) {
		sprintf(s, "%.1f", valueRefF);
	}
	else {
		sprintf(s, "%.0f", valueRefF);
	}
	refValue = s;
	TGrahics::outTextVertical(ref, ElementRect.Top + 22, ElementRect.Left, abs(colorState - 1), "Verdana12");
	TGrahics::outTextVertical(refValue, ElementRect.Top + 21, ElementRect.Left + 8, abs(colorState - 1), "Verdana12");
}

void Indicator::pointerH()
{
	percent = (valueRefF * 100) / valueOutMaxInt;

	if (valueRefF == 0) {
		yPosition = 25;
	}
	 else if (valueRefF >= valueOutMaxInt) {
		yPosition = 0;
	}
	else if (valueRefF < refMaxInt) {
		yPosition = 26 - (percent * 22) / 100;
	}
	else if (valueRefF >= refMaxInt) {
		yPosition = 26 - (percent * 22) / 100;
		//yPosition = 0;
	}
	else if (valueRefF <= refMinInt) {
		yPosition = 26 - (percent * 22) / 100;
	}
	TGrahics::Line(ElementRect.Left + 25, ElementRect.Top + 17 + yPosition, ElementRect.Left + 23, ElementRect.Top + 15 + yPosition, abs(colorState - 1));
	TGrahics::Line(ElementRect.Left + 24, ElementRect.Top + 17 + yPosition, ElementRect.Left + 22, ElementRect.Top + 15 + yPosition, abs(colorState - 1));
	TGrahics::Line(ElementRect.Left + 25, ElementRect.Top + 17 + yPosition, ElementRect.Left + 23, ElementRect.Top + 19 + yPosition, abs(colorState - 1));
	TGrahics::Line(ElementRect.Left + 24, ElementRect.Top + 17 + yPosition, ElementRect.Left + 22, ElementRect.Top + 19 + yPosition, abs(colorState - 1));
	TGrahics::Line(ElementRect.Left + 28, ElementRect.Top + 17 + yPosition, ElementRect.Left + 29, ElementRect.Top + 17 + yPosition, abs(colorState - 0));
}

bool Indicator::ProcessMessage(TMessage* m)
{
	switch (m->Event) {
	case (u32)EventSrc::KEYBOARD: {
		switch (m->p1) {
		case (u32)KeyCodes::ESC:
			if (inFocus) {
				TRouter::setTask({ false, "Home", nullptr });
			}
			break;
		case (u32)KeyCodes::Up:
			if (inFocus) {
				increase((m->p2 == (u32)KeyPressFeature::AutoRepeat) ? stepInt * 2 : stepInt);
			}
			break;
		case (u32)KeyCodes::Down:
			if (inFocus) {
				decrease((m->p2 == (u32)KeyPressFeature::AutoRepeat) ? stepInt * 2 : stepInt);
			}

			break;
		case (u32)KeyCodes::F1:
			if (inFocus) {
				ISignal* p = IniResources::getSignalByTag(nameValue);
				TRouter::setTask({ false, "Help", p });

			}
			break;
		}
	}
	for (auto& element : List) {
		element->ProcessMessage(m);
	}
	return false;
	}
}

void Indicator::setValueFB(float newValue)
{
	fillingBar.setValue(newValue);
}

float Indicator::getValueFB()
{
	return fillingBar.getValue();
}
void Indicator::scaleBar()
{
	fillingBar.scaleBarValue();
}

void Indicator::decrease(int step) {
	/*получить текущее значение Iref, вычесть из него 1A или 5А (в зависимости
	 однократное это нажатие или автоматический повтор)и передать на EFi
	значение может быть не числовое а "**.**" когда нет связи, значит
	1) получить значение 2) убедится что числовое 3) произвести над ним вычисления
	4) превратить  в строку 5) отправить */

	if ((valueRefF - step) <= refMinInt) {
		valueRefF = refMinInt;
	}
	else {
		valueRefF -= step;
	}
	char s[8];
	sprintf(s, "%.1f", valueRefF);
	refValue = s;
	sendCmd(refValue);
}

void Indicator::increase(int step) {
	/*получить текущее значение Iref, вычесть из него 1A или 5А (в зависимости
	 однократное это нажатие или автоматический повтор)и передать на EFi
	значение может быть не числовое а "**.**" когда нет связи, значит
	1) получить значение 2) убедится что числовое 3) произвести над ним вычисления
	4) превратить  в строку 5) отправить */

	if ((valueRefF + step) >= refMaxInt) {
		valueRefF = refMaxInt;
	}
	else {
		valueRefF += step;
	}
	char s[8];
	sprintf(s, "%.1f", valueRefF);
	refValue = s;
	sendCmd(refValue);

}

void Indicator::sendCmd(std::string& refValue) {
	std::string tag;
	if (nameRef == "U1/RAM/Uref/") {
		tag = "U1/RAM/Uref/";
	}
	else {
		tag = "U1/RAM/Ilim/";
	}
	cmdSendInProcess = true;
	ModbusSlave::setValue(tag, refValue, [this](Slot* slot, u8* reply) { SlotUpdate(slot, reply); });
}

void Indicator::SlotUpdate(Slot* slot, u8* reply) {
	slot->Flags |= (u16)SlotStateFlags::SKIP_SLOT;
	cmdSendInProcess = false;
}

void Indicator::updateObj(std::string sector, const TSlotHandlerArsg& args, const char* format) {
	if (sector == "RAM") {
		valueOut = objValueOut->getValue(args, "");
		refValue = objValueRef->getValue(args, "");
	}
	else if (sector == "FLASH") {
		valueRefMax = objValueRefMax->getValue(args, "");
		valueRefMin = objValueRefMin->getValue(args, "");
		valueStep = objStep->getValue(args, "");
		valueOutMax = objValueOutMax->getValue(args, "");
	}
	try {
		valueOutF = std::stof(valueOut);
		fillingBar.setValue(valueOutF);

		refMaxInt = std::stof(valueRefMax);
		if (nameRef == "U1/RAM/Ilim/") {
			refMinInt = 0;
		}
		else {
			refMinInt = std::stof(valueRefMin);
		}
		stepInt = std::stof(valueStep);
		valueOutMaxInt = std::stof(valueOutMax);
		fillingBar.setLimitValue(valueOutMaxInt);

		valueRefF = std::stof(refValue);
	}
	catch (...) {

		//valueOutF = 0;
		//valueOut = "**.*";
		//fillingBar.setValue(valueOutF);
		//valueRefF = 0;
		//maxValueInt = 0;
		//refValue = "0.0";
		//currentValue = "**.*";
	}
}