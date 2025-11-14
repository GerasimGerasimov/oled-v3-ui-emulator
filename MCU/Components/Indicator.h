#pragma once
#include "common.h"
#include <FillingBar.h>

class TParameter;
class ISignal;
class Slot;

class Indicator : public TVisualObject
{
private:
	std::string msu;
	std::string ref;
	std::string refValue;
	std::string valueOut;
	std::string valueRefMax;
	std::string valueRefMin;
	std::string valueStep;
	std::string valueOutMax;

	std::string nameRef;
	std::string nameValue;


	u8 colorState;

	FillingBar fillingBar;

	TParameter* objValueRef;
	TParameter* objValueOut;
	TParameter* objValueRefMax;
	TParameter* objValueRefMin;
	TParameter* objValueOutMax;
	TParameter* objStep;

	int percent;
	int yPosition = 25;
	int refMaxInt;
	int refMinInt;
	int valueOutMaxInt;
	float stepInt;

	float valueOutF;
	float valueRefF;//хранятся значения из I/U ref

	bool cmdSendInProcess;
	bool changeUref = false;

public:
	Indicator(int x, int y, std::string msu, std::string ref, std::string valueOut, std::string valueRef, std::string valueMax, std::string valueMin, std::string step, std::string valueOutMax);
	void view();
	const u16 getHeight(void);
	void drawBorder(int drawBorderX, int drawBorderY);
	void displayValue();
	void valueRef();
	void pointerH();
	bool ProcessMessage(TMessage* m);
	void setValueFB(float newValue);
	float getValueFB();
	void scaleBar();
	void decrease(float step);
	void increase(float step);
	void sendCmd(std::string& refValue);
	std::vector <TVisualObject*> List;
	void SlotUpdate(Slot* slot, u8* reply);
	void updateObj(std::string sector, const TSlotHandlerArsg& args, const char* format);
};