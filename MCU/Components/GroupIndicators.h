#pragma once
#include "common.h"
#include <stm32f4xx.h>

class TParameter;

class GroupIndicators : public TVisualObject
{
private:
	u8 colorState;
	std::string outValue1;
	std::string sparksV;
	float outVal;
	TParameter* objOut;
	TParameter* objSparks;

public:

	GroupIndicators(int x, int y, u8 colorState, std::string outValue1, std::string sparksV);
	void view() override;
	const u16 getHeight(void);
	void outValue();
	void sparksValue();
	void stateValue(char mode);
	void point();
	void invertOut();
	void update(const TSlotHandlerArsg& args, const char* format) override;

};

