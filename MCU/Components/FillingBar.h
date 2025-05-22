#pragma once

#include "common.h"
#include <stm32f4xx.h>

class FillingBar : public TVisualObject
{
private:
	float value = 0;
	int maxValue;
	int limitValue;
	u8 colorState;
public:
	FillingBar(int x, int y, u8 colorState, int limitValue, int maxValue);
	void view() override;
	const u16 getHeight(void) override;
	void drawBorder();
	void scaleBarFoam();
	void scaleBarValue();
	void pointerH(unsigned int yPosition);
	void pointerV();
	void drawThreshold();
	void setValue(float newValue);
	float getValue();
	void setColorState(u8 newColor);
};

