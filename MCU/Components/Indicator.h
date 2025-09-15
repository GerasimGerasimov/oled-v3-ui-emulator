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
	std::string currentValue;
	std::string maxValue;
	std::string limitValue;
	std::string nameRef;

	u8 colorState;

	FillingBar fillingBar;

	int percent;
	int yPosition = 25;
	int refMaxInt;
	int limValueInt;
	int stepInt;

	float ratio;
	float valuePoint;
	float value;//хранятся значения из I/U ref

	bool cmdSendInProcess;
	bool changeUref = false;

public:
	Indicator(int x, int y, std::string msu, std::string ref);
	void view();
	const u16 getHeight(void);
	void drawBorder(int drawBorderX, int drawBorderY);
	void displayValue();
	void valueRef();
	void pointerH();
	bool ProcessMessage(TMessage* m);
	void decrease(int step);
	void increase(int step);
	void sendCmd(std::string& refValue);
	std::vector <TVisualObject*> List;
	void SlotUpdate(Slot* slot, u8* reply);
};