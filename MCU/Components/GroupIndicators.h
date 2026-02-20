#pragma once
#include "common.h"
#include <stm32f4xx.h>
#include <array>

class TParameter;
class ISignal;
class Slot;

class GroupIndicators : public TVisualObject
{
private:
	u8 colorState;
	std::string ratio;
	std::string nameOut;
	std::string tRunValue;
	std::string newTime = "";

	int timeV;
	int hour;

	TParameter* objOut;

	float outVal;
	float editVal;

	bool cmdSendInProcess;
	bool changeUref = false;

public:

	GroupIndicators(int x, int y, u8 colorState, std::string tRun);
	void view() override;
	const u16 getHeight(void);
	void tValue();
	void updateObj(std::string sector, const TSlotHandlerArsg& args, const char* format) override;
	void timeValue();
	bool ProcessMessage(TMessage* m);
	void startEdit() override;
};

