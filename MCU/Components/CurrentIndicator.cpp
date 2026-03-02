#include "CurrentIndicator.h"
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
#include "ramdata.h"

CurrentIndicator::CurrentIndicator(int x, int y, std::string msu, std::string ref,
	std::string tag, std::string refValue, u8 colorState, std::string limitValue, std::string maxValue, std::string step)
	: fillingBar(x, y, colorState)
{
	ElementRect.Left = x;
	ElementRect.Top = y;
	ElementRect.Height = 65;
	ElementRect.Width = 42;
	this->msu = msu;
	this->ref = ref;
	this->colorState = colorState; // состояние цвета

	//this->ratio = ratio; // соотношение, при котором изменяется шкала
	obj = (TParameter*)IniResources::getSignalByTag(tag);
	objRef = (TParameter*)IniResources::getSignalByTag(refValue);
	refMax = (TParameter*)IniResources::getSignalByTag(maxValue);
	objLimit = (TParameter*)IniResources::getSignalByTag(limitValue);
	objStep = (TParameter*)IniResources::getSignalByTag(step);
	nameRef = tag;
	refName = refValue;
}

void CurrentIndicator::view()
{
	fillingBar.setColorState(colorState);
	drawBorder(ElementRect.Left, ElementRect.Top);
	displayValue();
	fillingBar.view();
	changeValue();
	fillingBar.scaleBarValue();
	if (inFocus) {
		colorState = 1;
	}
	else {
		colorState = 0;
	}
	valueRef();
	pointerH();
}

const u16 CurrentIndicator::getHeight(void)
{
	return u16(ElementRect.Height);
}

void CurrentIndicator::startEdit()
{
	editValue = valuePoint;
	inFocus = true;
}

void CurrentIndicator::drawBorder(int drawBorderX, int drawBorderY) {

	TFillRect background{ drawBorderX, drawBorderY, ElementRect.Width, ElementRect.Height, abs(colorState - 0) };
	TGrahics::fillRect(background);
	TFillRect drawBorder{ ElementRect.Left + 1, ElementRect.Top + 11, 19, 35, abs(colorState - 1) };
	TGrahics::drawBorder(drawBorder);
}

void CurrentIndicator::valueRef() //значение ref
{
	TGrahics::outTextVertical(ref, ElementRect.Top + 20, ElementRect.Left, abs(colorState - 1), "Verdana12");
	float val = inFocus ? editValue : valuePoint;
	char s[32];
	if (val < 100) {
		sprintf(s, "%.1f", val);
	}
	else {
		sprintf(s, "%.0f", val);
	}
	refValue = s;
	TGrahics::outTextVertical(refValue, ElementRect.Top + 19, ElementRect.Left + 8, abs(colorState - 1), "Verdana12");
	
}
void CurrentIndicator::displayValue() //I/U ref
{
	TGrahics::outText(msu, ElementRect.Left + 7, ElementRect.Top, abs(colorState - 1), "Verdana12");
}

void CurrentIndicator::changeValue() //вывод значения индекатора
{
	
	if (value > limitValueInt) {
		TFillRect outerBorder{ msu == "I, A" ? ElementRect.Left + 1  : ElementRect.Left + 9, ElementRect.Top + 52, 30, 9, 1 };
		TGrahics::fillRect(outerBorder);
		char s[32];
		if (currentValue != "***.**") {
			if (value < 100) {
				sprintf(s, "%.1f", value);
			}
			else {
				sprintf(s, "%.0f", value);
			}
		currentValue = s;
		}
		TGrahics::outText(currentValue, msu == "I, A" ? ElementRect.Left + 3 : ElementRect.Left + 12, ElementRect.Top + 52, 0, "Verdana12");
	}
	else {
		TFillRect outerBorder{ msu == "I, A" ? ElementRect.Left + 1 : ElementRect.Left + 9, ElementRect.Top + 52, 30, 9, 0 };
		TGrahics::fillRect(outerBorder);
		char s[32];
		if (currentValue != "***.**") {
			if (value < 100) {
				sprintf(s, "%.1f", value);
			}
			else {
				sprintf(s, "%.0f", value);
			}
			currentValue = s;
		}
		TGrahics::outText(currentValue, msu == "I, A" ? ElementRect.Left + 3 : ElementRect.Left + 12, ElementRect.Top + 52, 1, "Verdana12");
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
	percent = (valuePoint * 100) / limitValueInt;
	
	if (valuePoint < limitValueInt) {
		yPosition = 25 - (percent * 22) / 100;
	}
	else if (valuePoint >= limitValueInt) {
		yPosition = 0;
	}
	else {
		yPosition = 25;
	}
	TGrahics::Line(ElementRect.Left + 25, ElementRect.Top + 18 + yPosition, ElementRect.Left + 23, ElementRect.Top + 16 + yPosition, abs(colorState - 1));
	TGrahics::Line(ElementRect.Left + 24, ElementRect.Top + 18 + yPosition, ElementRect.Left + 22, ElementRect.Top + 16 + yPosition, abs(colorState - 1));
	TGrahics::Line(ElementRect.Left + 25, ElementRect.Top + 18 + yPosition, ElementRect.Left + 23, ElementRect.Top + 20 + yPosition, abs(colorState - 1));
	TGrahics::Line(ElementRect.Left + 24, ElementRect.Top + 18 + yPosition, ElementRect.Left + 22, ElementRect.Top + 20 + yPosition, abs(colorState - 1));
	TGrahics::Line(ElementRect.Left + 28, ElementRect.Top + 18 + yPosition, ElementRect.Left + 29, ElementRect.Top + 18 + yPosition, abs(colorState - 0));
} 

bool CurrentIndicator::ProcessMessage(TMessage* m)
{
	switch (m->Event) {
	case (u32)EventSrc::KEYBOARD: {
		switch (m->p1) {
		case (u32)KeyCodes::Up:
			if (inFocus) {
				increase((m->p2 == (u32)KeyPressFeature::AutoRepeat) ? stepFloat * 2 : stepFloat);
			}
			break;
		case (u32)KeyCodes::Down:
			if (inFocus) {
				decrease((m->p2 == (u32)KeyPressFeature::AutoRepeat) ? stepFloat * 2 : stepFloat);
			}
			
			break;
		case (u32)KeyCodes::F1:
			if (inFocus) {
				ISignal* p = IniResources::getSignalByTag(nameRef);
				TRouter::setTask({ false, "Help", p });
		
			}
			break;
		case (u32)KeyCodes::ESC:
			if (inFocus) {
				TRouter::setTask({ false, "Home", nullptr });
				editValue = valuePoint;
				inFocus = false;
			}
			break;
		
		case (u32)KeyCodes::ENT:
			if (inFocus) {

				char s[32];
				if (editValue < 100) {
					sprintf(s, "%.1f", editValue);
				}
				else {
					sprintf(s, "%.0f", editValue);
				}
				refValue = s;
				sendCmd(refValue);
				inFocus = false;
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

void CurrentIndicator::decrease(float step) {
	/*получить текущее значение Iref, вычесть из него 1A или 5А (в зависимости
	 однократное это нажатие или автоматический повтор)и передать на EFi
	значение может быть не числовое а "**.**" когда нет связи, значит
	1) получить значение 2) убедится что числовое 3) произвести над ним вычисления
	4) превратить  в строку 5) отправить */
		
	if ((editValue - step) < 0.1) {
	editValue = 0;
	}
	else {
		editValue -= step;
	}
		//sendCmd(refValue);
}

void CurrentIndicator::increase(float step) {
	/*получить текущее значение Iref, вычесть из него 1A или 5А (в зависимости
	 однократное это нажатие или автоматический повтор)и передать на EFi
	значение может быть не числовое а "**.**" когда нет связи, значит
	1) получить значение 2) убедится что числовое 3) произвести над ним вычисления
	4) превратить  в строку 5) отправить */

	if ((editValue + step) > maxValueInt) {
		editValue = maxValueInt;
	}
	else {
		editValue += step;
	}
	//sendCmd(refValue);
}

void CurrentIndicator::sendCmd(std::string& refValue) {
	std::string tag;
	if (refName == "U1/RAM/Iref/") {
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

void CurrentIndicator::SlotUpdate(Slot* slot, u8* reply) {
	slot->Flags |= (u16)SlotStateFlags::SKIP_SLOT;
	cmdSendInProcess = false;
}

void CurrentIndicator::updateObj(std::string sector, const TSlotHandlerArsg& args, const char* format)
{

	if (sector == "RAM") {
		currentValue = obj->getValue(args, "");
		refValue = objRef->getValue(args, "");
		//++RAM_DATA.data[0];
	}
	else {
		//++RAM_DATA.data[1];
		limitValue = objLimit->getValue(args, "");
		maxValue = refMax->getValue(args, "");
		valueStep = objStep->getValue(args, "");
	}

	try {
		value = std::stof(currentValue);
        fillingBar.setValue(value);

		valuePoint = std::stof(refValue);

		maxValueInt = std::stof(maxValue);
		fillingBar.setMaxValue(maxValueInt);

		limitValueInt = std::stof(limitValue);
		fillingBar.setLimitValue(limitValueInt);

		stepFloat = std::stof(valueStep);
	}
	catch (...) {

		//value = 0;
		//fillingBar.setValue(value);
		//valuePoint = 0;
		//maxValueInt = 0;
		//valuePoint = 0;
		//refValue = "0.0";
		//currentValue = "**.*";
	}
}