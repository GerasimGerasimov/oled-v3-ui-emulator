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
	std::string runValue;
	std::string readyValue;

	int timeV;
	int hour;

	TParameter* objOut;
	TParameter* objRun;
	TParameter* objReady;


	float outVal;
	float editVal;

	bool cmdSendInProcess;
	bool changeUref = false;

public:

	GroupIndicators(int x, int y, u8 colorState, std::string tRun, std::string run, std::string ready);
	void view() override;
	const u16 getHeight(void);
	void tValue();
	void stateValue();
	void updateObj(std::string sector, const TSlotHandlerArsg& args, const char* format) override;
	void timeValue();
	bool ProcessMessage(TMessage* m);
	void startEdit() override;
};

