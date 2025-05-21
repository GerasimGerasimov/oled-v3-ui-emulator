#pragma once

#include "common.h"
#include <stm32f4xx.h>
#include <FillingBar.h>

class CurrentIndicator : public TVisualObject
{
private:
	std::string msu;
	std::string ref;
	std::string current;
	FillingBar fillingBar;
	u8 colorState;

public: 

	CurrentIndicator(int x, int y, std::string msu, std::string ref, u8 colorState);
	void view() override;
	const u16 getHeight(void);
	void drawBorder(int drawBorderX, int drawBorderY);
	void displayValue();
	void changeValue(std::string current);
	void invertArea();
	void setValue(int newValue);
	int getValue();
	void invertStateColor();
	void scaleBar();
	bool ProcessMessage(TMessage* m);
	std::vector <TVisualObject*> List;
};

