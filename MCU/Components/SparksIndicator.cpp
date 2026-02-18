#include "SparksIndicator.h"
#include <graphics.h>
#include <parameters.h>
#include <IniResources.h>
#include <Router.h>

SparksIndicator::SparksIndicator(int x, int y, u8 colorState, std::string sparks) {
	ElementRect.Left = x;
	ElementRect.Top = y;
	ElementRect.Height = 30;
	ElementRect.Width = 29;
	this->colorState = colorState;
	objSparks = (TParameter*)IniResources::getSignalByTag(sparks);
	nameSparks = sparks;
}

void SparksIndicator::view()
{
	TFillRect background{ ElementRect.Left, ElementRect.Top, ElementRect.Width, ElementRect.Height, abs(colorState - 0) };
	TGrahics::fillRect(background);
	//TGrahics::Line(ElementRect.Left, ElementRect.Top + 32, ElementRect.Left + 26, ElementRect.Top + 32, abs(colorState - 1));
	TGrahics::outText("иск,с", ElementRect.Left, ElementRect.Top, abs(colorState - 1), "Verdana12");

	if (inFocus) {
		areaState();
	}
	else {
		colorState = 0;
	}
	sparksValue();
}
const u16 SparksIndicator::getHeight(void)
{
	return u16(ElementRect.Height);
}
void SparksIndicator::sparksValue()
{
	char s[8];
	//GIST "%.4X" преобразование числа в hex с заданным кол-вом значащих нулей
	/*if (outVal < 100) {
	//	sprintf(s, "%.1f", outVal);
	//}
	//else {
	//	sprintf(s, "%.0f", outVal);
	//}
	//outValue1 = s;*/
	TGrahics::outText("0", ElementRect.Left + 3, ElementRect.Top + 13, abs(colorState - 1), "Verdana12");
}


void SparksIndicator::updateObj(std::string sector, const TSlotHandlerArsg& args, const char* format)
{
	if (sector == "RAM") {
		sparks = objSparks->getValue(args, "");
	}

}

bool SparksIndicator::ProcessMessage(TMessage* m) {
	switch (m->Event) {
	case (u32)EventSrc::KEYBOARD: {
		switch (m->p1) {
		case (u32)KeyCodes::F1:
			if (inFocus) {
				ISignal* p = IniResources::getSignalByTag(nameSparks);
				TRouter::setTask({ false, "Help", p });
			}
			break;
		case (u32)KeyCodes::ENT:
			if (inFocus) {
				inFocus = false;
			}
			break;
		}

		return false;
	}
	}
}
void SparksIndicator::areaState() {

	TFillRect selectionArea{ ElementRect.Left, ElementRect.Top, ElementRect.Width - 2, 9 };
	TGrahics::InvertArea(selectionArea);

}
void SparksIndicator::startEdit() {
	inFocus = true;
}


