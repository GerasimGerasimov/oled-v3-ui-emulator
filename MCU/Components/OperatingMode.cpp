#include "OperatingMode.h"
#include "graphics.h"
#include <iostream>
#include <cmath>

OperatingMode::OperatingMode(int x, int y, u8 colorState) {
	ElementRect.Left = x;
	ElementRect.Top = y;
	ElementRect.Height = 63;
	ElementRect.Width = 17;
	this->colorState = colorState;
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
	
	if (inFocus) {
		colorState = 1;
	}
	else {
		colorState = 0;
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
void OperatingMode::setYPosition(unsigned int newYPosition)
{
	yPosition = newYPosition;
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
				if (yPosition > 0) {
					setYPosition(getYPosition() - 1);
				}
				else {
					yPosition = 3;
				}
			}
			break;
		case (u32)KeyCodes::Down:
			if (inFocus) {
				if (yPosition < 3) {
					setYPosition(getYPosition() + 1);
				}
				else {
					yPosition = 0;
				};
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