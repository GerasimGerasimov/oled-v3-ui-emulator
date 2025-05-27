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

CurrentIndicator::CurrentIndicator(int x, int y, std::string msu, std::string ref, std::string tag, std::string read, u8 colorState, int limitValue, int maxValue, float ratio) : fillingBar(x, y, colorState, limitValue, maxValue, value) {
	ElementRect.Left = x;
	ElementRect.Top = y;
	ElementRect.Height = 63;
	ElementRect.Width = 40;
	this->msu = msu;
	this->read = read;
	this->ref = ref;
	this->colorState = colorState; // состояние цвета
	this->limitValue = limitValue; // пороговое значение
	this->maxValue = maxValue; // максимальное значение ref
	this->ratio = ratio; // соотношение, при котором изменяется шкала
	//this->valuePoint = valuePoint; // значение ref
	obj = (TParameter*)IniResources::getSignalByTag(tag);
	//std::string temp = obj->getValue();
	this->valuePoint = std::stof(read);//std::stof(read);
	
}

void CurrentIndicator::view()
{
	fillingBar.setColorState(colorState);
	drawBorder(ElementRect.Left, ElementRect.Top);
	displayValue();
	fillingBar.view();
	changeValue();
	fillingBar.scaleBarValue();
	fillingBar.setValue(value);
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

	TFillRect background{ drawBorderX, drawBorderY, ElementRect.Width, ElementRect.Height, std::fabs(colorState - 0) };
	TGrahics::fillRect(background);
	TFillRect outerBorder{ drawBorderX + 1, drawBorderY + 15, ElementRect.Width - 20, ElementRect.Height - 33, std::fabs(colorState - 1)};
	TGrahics::fillRect(outerBorder);
	TFillRect intBorder{ drawBorderX + 2, drawBorderY + 16, ElementRect.Width - 22, ElementRect.Height - 35, std::fabs(colorState - 0) };
	TGrahics::fillRect(intBorder);
}

void CurrentIndicator::valueRef() //значение ref
{
	TGrahics::outTextVertical(ref, ElementRect.Top + 22, ElementRect.Left, std::fabs(colorState - 1), "Verdana12");
	char s[8];
	//GIST "%.4X" преобразование числа в hex с заданным кол-вом значащих нулей
	if (getValueRef() < 100) {
		sprintf(s, "%.1f", getValueRef());
	}
	else {
		sprintf(s, "%.0f", getValueRef());
	}
	read = s;
	TGrahics::outTextVertical(read, ElementRect.Top + 21, ElementRect.Left + 8, std::fabs(colorState - 1), "Verdana12");
	pointerH();
}
void CurrentIndicator::displayValue() //I/U ref
{
	TGrahics::outText(msu, ElementRect.Left + 3, ElementRect.Top + 2, std::fabs(colorState - 1), "Verdana12");
}

void CurrentIndicator::changeValue() //вывод значения индекатора
{
	if (fillingBar.getValue() > limitValue) {
		TFillRect outerBorder{ ElementRect.Left + 6, ElementRect.Top + 50, 30, 9, 1 };
		TGrahics::fillRect(outerBorder);
		//char s[8];
		////GIST "%.4X" преобразование числа в hex с заданным кол-вом значащих нулей
		//if (fillingBar.getValue() < 100) {
		//	sprintf(s, "%.1f", getValue());
		//}
		//else {
		//	sprintf(s, "%.0f", getValue());
		//}
		//current = s;
		TGrahics::outText(current, ElementRect.Left + 7, ElementRect.Top + 50, 0, "Verdana12");
	}
	else {
		TFillRect outerBorder{ ElementRect.Left + 6, ElementRect.Top + 50, 30, 9, 0 };
		TGrahics::fillRect(outerBorder);
		//char s[8];
		//GIST "%.4X" преобразование числа в hex с заданным кол-вом значащих нулей
		/*if (fillingBar.getValue() < 100) {
			sprintf(s, "%.1f", getValue());
		}
		else {
			sprintf(s, "%.0f", getValue());
		}
		current = s;*/
		TGrahics::outText(current, ElementRect.Left + 7, ElementRect.Top + 50, 1, "Verdana12");
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
	if (newValueRef > maxValue) {
		newValueRef = maxValue;
	}
	else if (newValueRef < 0) {
		newValueRef = 0;
	}
	valuePoint = newValueRef;
}

float CurrentIndicator::getValueRef()
{
	return valuePoint;
}

void CurrentIndicator::pointerH() //стрелка горизонтальная
{
	int percent = 0;
	int yPosition = 0;
	percent = (valuePoint * 100) / maxValue;
	yPosition = 25 - (percent * 25) / 100;
	TGrahics::Line(ElementRect.Left + 25, ElementRect.Top + 18 + yPosition, ElementRect.Left + 23, ElementRect.Top + 16 + yPosition, std::fabs(colorState - 1));
	TGrahics::Line(ElementRect.Left + 24, ElementRect.Top + 18 + yPosition, ElementRect.Left + 22, ElementRect.Top + 16 + yPosition, std::fabs(colorState - 1));
	TGrahics::Line(ElementRect.Left + 25, ElementRect.Top + 18 + yPosition, ElementRect.Left + 23, ElementRect.Top + 20 + yPosition, std::fabs(colorState - 1));
	TGrahics::Line(ElementRect.Left + 24, ElementRect.Top + 18 + yPosition, ElementRect.Left + 22, ElementRect.Top + 20 + yPosition, std::fabs(colorState - 1));
	TGrahics::Line(ElementRect.Left + 28, ElementRect.Top + 18 + yPosition, ElementRect.Left + 29, ElementRect.Top + 18 + yPosition, std::fabs(colorState - 0));
} 

bool CurrentIndicator::ProcessMessage(TMessage* m)
{
	switch (m->Event) {
	case (u32)EventSrc::KEYBOARD: {
		switch (m->p1) {
		case (u32)KeyCodes::Up:
			if (inFocus) {
				//setValue(getValue() + 85 * ratio);
				setValueRef(getValueRef() + 85 * ratio);
			}
			break;
		case (u32)KeyCodes::Down:
			if (inFocus) {
				//setValue(getValue() - 85 * ratio);
				setValueRef(getValueRef() - 85 * ratio);
			}
			
			break;
		case (u32)KeyCodes::F1:
			if (inFocus) {
				if (fillingBar.getValue() < value || fillingBar.getValue() > value) {
					fillingBar.setValue(value);
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

void CurrentIndicator::update(const TSlotHandlerArsg& args, const char* format)
{
	current = obj->getValue(args, "");
	try {
		//char s[8];
		////GIST "%.4X" преобразование числа в hex с заданным кол-вом значащих нулей
		/*if (getValueRef() < 100) {
			sprintf(s, "%.1f", getValueRef());
		}
		else {
			sprintf(s, "%.0f", getValueRef());
		}*/
		//read = s;
		value = std::stof(current);
		valuePoint = std::stof(read);
		//read == "unknown";
		//valuePoint = 0;
		//current = std::to_string(valuePoint);
	}
	catch (...)  {
		value = 0;
		valuePoint = 0;
		//valuePoint = std::stof(read);
		read = "0.0";
		current = "**.*";
	}
	
}

