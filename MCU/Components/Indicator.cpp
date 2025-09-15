#include "Indicator.h"
#include <graphics.h>
#include "Router.h"
#include "parameters.h"
#include "PageHome.h"
#include "IniResources.h"
#include <string>
#include "AppModbusSlave.h"
#include "Slot.h"


Indicator::Indicator(int x, int y, std::string msu, std::string ref) : fillingBar(x, y, colorState) {
	ElementRect.Left = x;
	ElementRect.Top = y;
	ElementRect.Height = 63;
	ElementRect.Width = 40;
	this->msu = msu;
	this->ref = ref;
	this->colorState = colorState; // состояние цвета
}

void Indicator::view() {
	drawBorder(ElementRect.Left, ElementRect.Top);
	if (inFocus) {
		colorState = 1;
	}
	else {
		colorState = 0;
	}
	fillingBar.view();
	displayValue();
	valueRef();
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
	TGrahics::outText(msu, ElementRect.Left + 3, ElementRect.Top + 2, abs(colorState - 1), "Verdana12");
}

void Indicator::valueRef() //значение ref
{
	TGrahics::outTextVertical(ref, ElementRect.Top + 22, ElementRect.Left, abs(colorState - 1), "Verdana12");
	TGrahics::outTextVertical("1000", ElementRect.Top + 21, ElementRect.Left + 8, abs(colorState - 1), "Verdana12");

}

void Indicator::pointerH()
{
	percent = (valuePoint * 100) / limValueInt;

	if (valuePoint == 0) {
		yPosition = 25;
	}
	else if (valuePoint >= limValueInt) {
		yPosition = 0;
	}
	else if (valuePoint < refMaxInt) {
		yPosition = 26 - (percent * 22) / 100;
	}
	else if (valuePoint >= refMaxInt) {
		valuePoint = refMaxInt;
		percent = (valuePoint * 100) / limValueInt;
		yPosition = 26 - (percent * 22) / 100;
		//yPosition = 0;
	}
	TGrahics::Line(ElementRect.Left + 25, ElementRect.Top + 18 + yPosition, ElementRect.Left + 23, ElementRect.Top + 16 + yPosition, abs(colorState - 1));
	TGrahics::Line(ElementRect.Left + 24, ElementRect.Top + 18 + yPosition, ElementRect.Left + 22, ElementRect.Top + 16 + yPosition, abs(colorState - 1));
	TGrahics::Line(ElementRect.Left + 25, ElementRect.Top + 18 + yPosition, ElementRect.Left + 23, ElementRect.Top + 20 + yPosition, abs(colorState - 1));
	TGrahics::Line(ElementRect.Left + 24, ElementRect.Top + 18 + yPosition, ElementRect.Left + 22, ElementRect.Top + 20 + yPosition, abs(colorState - 1));
	TGrahics::Line(ElementRect.Left + 28, ElementRect.Top + 18 + yPosition, ElementRect.Left + 29, ElementRect.Top + 18 + yPosition, abs(colorState - 0));
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
				//increase((m->p2 == (u32)KeyPressFeature::AutoRepeat) ? stepInt * 2 : stepInt);
			}
			break;
		case (u32)KeyCodes::Down:
			if (inFocus) {
				//decrease((m->p2 == (u32)KeyPressFeature::AutoRepeat) ? stepInt * 2 : stepInt);
			}

			break;
		case (u32)KeyCodes::F1:
			if (inFocus) {
				/*ISignal* p = IniResources::getSignalByTag(nameValue);
				TRouter::setTask({ false, "Help", p });*/

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

void Indicator::decrease(int step) {
	/*получить текущее значение Iref, вычесть из него 1A или 5А (в зависимости
	 однократное это нажатие или автоматический повтор)и передать на EFi
	значение может быть не числовое а "**.**" когда нет связи, значит
	1) получить значение 2) убедится что числовое 3) произвести над ним вычисления
	4) превратить  в строку 5) отправить */

	if ((valuePoint - stepInt) <= 0) {
		valuePoint = 0;
	}
	else {
		valuePoint -= stepInt;
	}
	char s[8];
	if (valuePoint < 100) {
		sprintf(s, "%.1f", valuePoint);
	}
	else {
		sprintf(s, "%.0f", valuePoint);
	}
	refValue = s;
	sendCmd(refValue);
}

void Indicator::increase(int step) {
	/*получить текущее значение Iref, вычесть из него 1A или 5А (в зависимости
	 однократное это нажатие или автоматический повтор)и передать на EFi
	значение может быть не числовое а "**.**" когда нет связи, значит
	1) получить значение 2) убедится что числовое 3) произвести над ним вычисления
	4) превратить  в строку 5) отправить */

	if ((valuePoint + stepInt) >= refMaxInt) {
		valuePoint = refMaxInt;
		char s[8];
		if (valuePoint < 100) {
			sprintf(s, "%.1f", valuePoint);
		}
		else {
			sprintf(s, "%.0f", valuePoint);
		}
		refValue = s;
		sendCmd(refValue);
	}
	else {
		valuePoint += stepInt;
	}
	char s[8];
	if (valuePoint < 100) {
		sprintf(s, "%.1f", valuePoint);
	}
	else {
		sprintf(s, "%.0f", valuePoint);
	}
	refValue = s;
	sendCmd(refValue);
}

void Indicator::sendCmd(std::string& refValue) {
	std::string tag;
	if (nameRef == "U1/RAM/Iref/") {
		tag = "U1/RAM/Iref/";
	}
	else {
		tag = "U1/RAM/Uref/";
	}
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

void Indicator::SlotUpdate(Slot* slot, u8* reply) {
	slot->Flags |= (u16)SlotStateFlags::SKIP_SLOT;
	cmdSendInProcess = false;
}