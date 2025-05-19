#pragma once

#include "common.h"
#include <stm32f4xx.h>
#include <FillingBar.h>

class CurrentIndicator : public TVisualObject
{
private:
	int height = 63;
	int width = 40;
	int x, y;
	std::string msu;
	FillingBar fillingBar;
	std::string current;

public: 

	CurrentIndicator(int x, int y, std::string msu);
	void view() override;
	const u16 getHeight(void);

	void drawBorder(int drawBorderX, int drawBorderY);
	void displayValue();

	void changeValue(std::string current);
	void invertArea();
	
	void setValue(int newValue);
	int getValue();
};

