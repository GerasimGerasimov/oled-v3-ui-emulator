#include "CurrentIndicator.h"
#include "graphics.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cmath>
#include <Router.h>
#include "parameters.h"
#include <PageHome.h>
#include "IniResources.h"
#include <string>

CurrentIndicator::CurrentIndicator(int x, int y, std::string msu, std::string ref, 
	std::string tag, std::string refValue, u8 colorState, std::string limitValue, std::string maxValue, float ratio)
	: fillingBar(x, y, colorState)
{
	ElementRect.Left = x;
	ElementRect.Top = y;
	ElementRect.Height = 63;
	ElementRect.Width = 40;
	this->msu = msu;
	this->ref = ref;
	this->colorState = colorState; // состояние цвета
	this->ratio = ratio; // соотношение, при котором изменяется шкала
	//this->valuePoint = valuePoint; // значение ref
	obj = (TParameter*)IniResources::getSignalByTag(tag);
	objRef = (TParameter*)IniResources::getSignalByTag(refValue);
	refMax = (TParameter*)IniResources::getSignalByTag(maxValue);
	objLimit = (TParameter*)IniResources::getSignalByTag(limitValue);
	//std::string temp = obj->getValue();
	//this->valuePoint = std::stof(read);//std::stof(read);
	
}

void CurrentIndicator::view()
{
	fillingBar.setColorState(colorState);
	drawBorder(ElementRect.Left, ElementRect.Top);
	displayValue();
	fillingBar.view();
	changeValue();
	fillingBar.scaleBarValue();
	//fillingBar.setValue(value);
	if (inFocus) {
		colorState = 1;
	}
	else {
		colorState = 0;
	}
	valueRef();
}

const u16 CurrentIndicator::getHeight(void)
{
	return u16(ElementRect.Height);
}

void CurrentIndicator::drawBorder(int drawBorderX, int drawBorderY) {

	TFillRect background{ drawBorderX, drawBorderY, ElementRect.Width, ElementRect.Height, abs(colorState - 0) };
	TGrahics::fillRect(background);
	TFillRect outerBorder{ drawBorderX + 1, drawBorderY + 15, ElementRect.Width - 20, ElementRect.Height - 33, abs(colorState - 1)};
	TGrahics::fillRect(outerBorder);
	TFillRect intBorder{ drawBorderX + 2, drawBorderY + 16, ElementRect.Width - 22, ElementRect.Height - 35, abs(colorState - 0) };
	TGrahics::fillRect(intBorder);
}


void CurrentIndicator::update(const TSlotHandlerArsg& args, const char* format)
{
	current = obj->getValue(args, "");
	refValue = objRef->getValue(args, "");
	maxValue = refMax->getValue(args, "");
	limitValue = objLimit->getValue(args, "");

	try {
		value = std::stof(current);
		fillingBar.setValue(value);

		char s[8];
		//GIST "%.4X" преобразование числа в hex с заданным кол-вом значащих нулей
		if (value < 100) {
			sprintf(s, "%.1f", value);
		}
		else {
			sprintf(s, "%.0f", value);
		}
		current = s;

		valuePoint = std::stof(refValue);
		if (valuePoint < 100) {
			sprintf(s, "%.1f", valuePoint);
		}
		else {
			sprintf(s, "%.0f", valuePoint);
		}
		refValue = s;

		maxValueInt = std::stof(maxValue);
		fillingBar.setMaxValue(maxValueInt);

		limitValueInt = std::stof(limitValue);
		fillingBar.setLimitValue(limitValueInt);
	}
	catch (...) {
		value = 0;
		fillingBar.setValue(value);
		valuePoint = 0;
		maxValueInt = 0;

		refValue = "0.0";
		current = "**.*";
		//maxValue = "**.*";
	}

}

void CurrentIndicator::valueRef() //значение ref
{
	TGrahics::outTextVertical(ref, ElementRect.Top + 22, ElementRect.Left, abs(colorState - 1), "Verdana12");
	TGrahics::outTextVertical(refValue, ElementRect.Top + 21, ElementRect.Left + 8, abs(colorState - 1), "Verdana12");
	pointerH();
}
void CurrentIndicator::displayValue() //I/U ref
{
	TGrahics::outText(msu, ElementRect.Left + 3, ElementRect.Top + 2, abs(colorState - 1), "Verdana12");
}

void CurrentIndicator::changeValue() //вывод значения индекатора
{
	if (value > limitValueInt) {
		TFillRect outerBorder{ ElementRect.Left + 9, ElementRect.Top + 50, 30, 9, 1 };
		TGrahics::fillRect(outerBorder);
		TGrahics::outTextRightToLeft(current, ElementRect.Left + 17, ElementRect.Top + 50, 0, "Verdana12");
	}
	else {
		TFillRect outerBorder{ ElementRect.Left + 6, ElementRect.Top + 50, 30, 9, 0 };
		TGrahics::fillRect(outerBorder);
		TGrahics::outText(current, ElementRect.Left + 12, ElementRect.Top + 50, 1, "Verdana12");
	}
}

void CurrentIndicator::invertArea() //инвертирование области
{
	TFillRect selectionArea{ ElementRect.Left, ElementRect.Top, ElementRect.Width, ElementRect.Height };
	TGrahics::InvertArea(selectionArea);
}

void CurrentIndicator::setValue(float newValue)
{
	fillingBar.setValue(newValue);
}

float CurrentIndicator::getValue()
{
	return fillingBar.getValue();
}
void CurrentIndicator::scaleBar()
{
	fillingBar.scaleBarValue();
}

void CurrentIndicator::setValueRef(float newValueRef)
{
	if (newValueRef > limitValueInt) {
		newValueRef = limitValueInt;
	}
	else if (newValueRef < 0) {
		newValueRef = 0;
	}
	valuePoint = newValueRef;

}

float CurrentIndicator::getValueRef()
{
	
	refValue = std::to_string(valuePoint);

	char s[8];
	if (valuePoint < 100) {
		sprintf(s, "%.1f", valuePoint);
	}
	else {
		sprintf(s, "%.0f", valuePoint);
	}
	refValue = s;
	return valuePoint;
}

void CurrentIndicator::setMaxValue(int newMaxValue) 
{
	maxValueInt = newMaxValue;
}
int CurrentIndicator::getMaxValue()
{
	return maxValueInt;
}

void CurrentIndicator::pointerH() //стрелка горизонтальная 
{
	int percent = 0;
	int yPosition = 0;
	percent = (valuePoint * 100) / limitValueInt;
	yPosition = 25 - (percent * 25) / 100;
	if (valuePoint < limitValueInt) {
		TGrahics::Line(ElementRect.Left + 25, ElementRect.Top + 18 + yPosition, ElementRect.Left + 23, ElementRect.Top + 16 + yPosition, abs(colorState - 1));
		TGrahics::Line(ElementRect.Left + 24, ElementRect.Top + 18 + yPosition, ElementRect.Left + 22, ElementRect.Top + 16 + yPosition, abs(colorState - 1));
		TGrahics::Line(ElementRect.Left + 25, ElementRect.Top + 18 + yPosition, ElementRect.Left + 23, ElementRect.Top + 20 + yPosition, abs(colorState - 1));
		TGrahics::Line(ElementRect.Left + 24, ElementRect.Top + 18 + yPosition, ElementRect.Left + 22, ElementRect.Top + 20 + yPosition, abs(colorState - 1));
		TGrahics::Line(ElementRect.Left + 28, ElementRect.Top + 18 + yPosition, ElementRect.Left + 29, ElementRect.Top + 18 + yPosition, abs(colorState - 0));
	}
	else if (valuePoint > limitValueInt) {
		TGrahics::Line(ElementRect.Left + 25, ElementRect.Top + 22, ElementRect.Left + 23, ElementRect.Top + 20, abs(colorState - 1));
		TGrahics::Line(ElementRect.Left + 24, ElementRect.Top + 22, ElementRect.Left + 22, ElementRect.Top + 20, abs(colorState - 1));
		TGrahics::Line(ElementRect.Left + 25, ElementRect.Top + 22, ElementRect.Left + 23, ElementRect.Top + 24, abs(colorState - 1));
		TGrahics::Line(ElementRect.Left + 24, ElementRect.Top + 22, ElementRect.Left + 22, ElementRect.Top + 24, abs(colorState - 1));
		TGrahics::Line(ElementRect.Left + 28, ElementRect.Top + 22, ElementRect.Left + 29, ElementRect.Top + 22, abs(colorState - 0));
	}
	else {
		TGrahics::Line(ElementRect.Left + 25, ElementRect.Top + 43, ElementRect.Left + 23, ElementRect.Top + 41, abs(colorState - 1));
		TGrahics::Line(ElementRect.Left + 24, ElementRect.Top + 43, ElementRect.Left + 22, ElementRect.Top + 41, abs(colorState - 1));
		TGrahics::Line(ElementRect.Left + 25, ElementRect.Top + 43, ElementRect.Left + 23, ElementRect.Top + 45, abs(colorState - 1));
		TGrahics::Line(ElementRect.Left + 24, ElementRect.Top + 43, ElementRect.Left + 22, ElementRect.Top + 45, abs(colorState - 1));
		TGrahics::Line(ElementRect.Left + 28, ElementRect.Top + 43, ElementRect.Left + 29, ElementRect.Top + 43, abs(colorState - 0));
	}
} 

bool CurrentIndicator::ProcessMessage(TMessage* m)
{
	switch (m->Event) {
	case (u32)EventSrc::KEYBOARD: {
		switch (m->p1) {
		case (u32)KeyCodes::Up:
			if (inFocus) {
				//setValue(getValue() + 85 * ratio);
				setValueRef(getValueRef() + 10 * ratio);

			}
			break;
		case (u32)KeyCodes::Down:
			if (inFocus) {
				//setValue(getValue() - 85 * ratio);
				setValueRef(getValueRef() - 10 * ratio);
			}
			
			break;
		case (u32)KeyCodes::F1:
			if (inFocus) {
				if (fillingBar.getValue() < valuePoint || fillingBar.getValue() > valuePoint) {
					fillingBar.setValue(valuePoint);
				}
				setValue(getValue());
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


