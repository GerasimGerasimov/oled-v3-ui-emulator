#pragma once

#include "common.h"
#include <stm32f4xx.h>
#include <FillingBar.h>
#include <Label.h>

class TParameter;
class Slot;

class CurrentIndicator : public TVisualObject
{
private:
	std::string msu;
	std::string ref;
	std::string refValue;
	std::string currentValue;
	std::string maxValue;
	std::string limitValue;
	std::string nameRef;
	std::string refName;

	FillingBar fillingBar;

	u8 colorState;

	int limitValueInt;  //I/U outNominal
	int maxValueInt;    //IOutMax
	int percent;
	int yPosition;

	//float ratio;		//соотношение, при котором рисуется шкала FillingBar
	float value;        //хранятся значение из I/U outAve
	float valuePoint;   //хранятся значения из I/U ref

	TParameter* obj;    //I/U outAve
	TParameter* objRef; //I/U ref
	TParameter* refMax; //I/U max
	TParameter* objLimit; // I/U out Nominal
	
	bool cmdSendInProcess;
	bool changeUref = false;

	float editValue;   // временное значение для UI
	bool editMode;
	//u16 TryCount;

public: 

	CurrentIndicator(int x, 
		int y, 
		std::string msu, 
		std::string ref, 
		std::string tag, 
		std::string refValue, 
		u8 colorState, 
		std::string limitValue, 
		std::string maxValue, 
		std::string step);
	void view() override;
	const u16 getHeight(void);
	void startEdit() override;
	void drawBorder(int drawBorderX, int drawBorderY);
	void valueRef();
	void displayValue();
	void changeValue();
	void invertArea();
	void setValue(float newValue);
	float getValue();
	void scaleBar();
	void pointerH();
	void setValueRef(float newValueRef);
	float getValueRef();
	void setMaxValue(int newMaxValue);
	int getMaxValue();
	bool ProcessMessage(TMessage* m);
	void decrease(float step);
	void sendCmd(std::string& value);
	void SlotUpdate(Slot* slot, u8* reply);
	void increase(float step);
	std::vector <TVisualObject*> List;
	void updateObj(std::string sector, const TSlotHandlerArsg& args, const char* format) override;
};

