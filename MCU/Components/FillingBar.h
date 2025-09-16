#pragma once
#include "common.h"
class FillingBar : public TVisualObject
{
private:
	std::string msu;
	std::string ref;
	std::string refValue;
	std::string tag;
	float value;
	float ratio;
	int maxValueInt;
	int limitValue;
	u8 colorState;

public:
	FillingBar(int x, int y, u8 colorState);
	void view() override;
	const u16 getHeight(void) override;
	void drawBorder();
	void scaleBarFoam();
	void scaleBarValue();
	//void pointerH(unsigned int yPosition);
	void pointerV();
	void drawThreshold();
	void setValue(float newValue);
	float getValue();
	void setColorState(u8 newColor);
	void setLimitValue(int newLimitValue);
};

