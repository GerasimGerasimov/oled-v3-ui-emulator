#pragma once
#include <common.h>
class OperatingMode : public TVisualObject
{
private:
	u8 colorState;
	unsigned int yPosition = 0;
public:

	OperatingMode(int x, int y, u8 colorState);
	void view() override;
	const u16 getHeight(void);
	void background();
	void drawBorder();
	void stateValue(u8 newColor);
	int getYPosition();
	void setYPosition(unsigned int newYPosition);
	void hidingBorder();
	bool ProcessMessage(TMessage* m);
	std::vector <TVisualObject*> List;
	std::vector <TVisualObject*> modeConteiner;
};

