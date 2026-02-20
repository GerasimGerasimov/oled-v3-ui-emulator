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
	std::string outValue1;
	std::string ratio;
	std::string nameOut;

	TParameter* objOut;

	float outVal;
	float editVal;

	bool cmdSendInProcess;
	bool changeUref = false;

public:

	GroupIndicators(int x, int y, u8 colorState, std::string outValue1);
	void view() override;
	const u16 getHeight(void);
	void outValue();
	void updateObj(std::string sector, const TSlotHandlerArsg& args, const char* format) override;
	bool ProcessMessage(TMessage* m);
	//void decrease(float step);
	//void increase(float step);
	void sendCmd(std::string& refValue);
	void SlotUpdate(Slot* slot, u8* reply);
	void areaState();
	void startEdit() override;
};

