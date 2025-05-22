#pragma once

#include "common.h"
#include <stm32f4xx.h>
#include <FillingBar.h>

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

public: 

	CurrentIndicator(int x, int y, std::string msu, std::string ref, std::string read, u8 colorState, int limitValue, int maxValue, float ratio);
	void view() override;
	const u16 getHeight(void);
	void drawBorder(int drawBorderX, int drawBorderY);
	void displayValue();
	void changeValue(std::string current);
	void invertArea();
	void setValue(float newValue);
	float getValue();
	void invertStateColor();
	void scaleBar();
	bool ProcessMessage(TMessage* m);
	std::vector <TVisualObject*> List;
};

