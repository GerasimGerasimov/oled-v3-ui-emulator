#pragma once
#include "common.h"
class GroupIndicators : public TVisualObject
{
private:
	u8 colorState;

public:

	GroupIndicators(int x, int y, u8 colorState);
	void view() override;
	const u16 getHeight(void);
	void outValue(std::string outValue);
	void sparksValue(std::string sparksValue);
	void stateValue(char mode);
	void point();
	void invertOut();

};

