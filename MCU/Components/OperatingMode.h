#pragma once
#include <common.h>
class OperatingMode : public TVisualObject
{
private:
	int height = 63;
	int width = 17;
	int x , y;
public:

	OperatingMode(int x, int y);
	void view() override;
	const u16 getHeight(void);
	void drawBorder(unsigned int yPosition);

};

