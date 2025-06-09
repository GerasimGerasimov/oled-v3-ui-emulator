#pragma once
#include "common.h"
#include <stm32f4xx.h>
#include <array>

class TParameter;
class ISignal;

class GroupIndicators : public TVisualObject
{
private:
	u8 colorState;
	std::string outValue1;
	std::string sparksV;
	std::string ready;
	std::string run;
	std::string ratio;

	std::string readyValue;
	std::string runValue;

	float outVal;
	TParameter* objOut;
	TParameter* objSparks;
	TParameter* objReady;
	TParameter* objRun;
	char mode;
	std::array <ISignal*, 4> container;
	int component = 0;
	int yPos = 0;

public:

	GroupIndicators(int x, int y, u8 colorState, std::string outValue1, std::string sparksV, std::string ready, std::string run);
	void view() override;
	const u16 getHeight(void);
	void outValue();
	void sparksValue();
	void stateValue();
	void editStateValue();
	void setStateValue();
	void point();
	//void invertOut();
	void updateObj(std::string sector, const TSlotHandlerArsg& args, const char* format) override;
	bool ProcessMessage(TMessage* m);
	void areaState(unsigned int yPos);
};

