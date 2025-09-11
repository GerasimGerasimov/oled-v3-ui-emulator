#pragma once
#include "common.h"
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

public:
	Indicator(int x, int y, std::string msu, std::string ref);
	void view();
	const u16 getHeight(void);
	void drawBorder(int drawBorderX, int drawBorderY);
	void displayValue();
};

