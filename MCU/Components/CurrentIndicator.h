#pragma once

#include "common.h"
#include <stm32f4xx.h>
#include <FillingBar.h>

class TParameter;

class CurrentIndicator : public TVisualObject
{
private:
	std::string msu;
	std::string ref;
	std::string read;
	std::string current;
	FillingBar fillingBar;
	u8 colorState;
	int limitValue;
	int maxValue;
	float ratio;
	float value;
	float valuePoint;
	TParameter* obj;

public: 

	CurrentIndicator(int x, int y, std::string msu, std::string ref, std::string tag, std::string read, u8 colorState, int limitValue, int maxValue, float ratio);
	void view() override;
	const u16 getHeight(void);
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
	bool ProcessMessage(TMessage* m);
	std::vector <TVisualObject*> List;
	void update(const TSlotHandlerArsg& args, const char* format) override;
};

