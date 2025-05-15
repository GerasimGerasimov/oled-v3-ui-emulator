#pragma once

#include "common.h"
#include <stm32f4xx.h>

class FillingBar : public TVisualObject
{
private:
	int height = 28;
	int width = 12;
	int x, y;
public:
	FillingBar(int x, int y);
	void view() override;
	const u16 getHeight(void) override;
	void drawBorder();
	void scaleBar();
	void scaleBarValue();
	void pointerH(unsigned int yPosition);
	void pointerV();
};

