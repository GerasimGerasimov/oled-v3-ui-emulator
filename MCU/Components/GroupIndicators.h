#pragma once
#include "common.h"
#include <stm32f4xx.h>
#include <Label.h>
#include <array>

class TParameter;
class ISignal;

class GroupIndicators : public TVisualObject
{
private:
	std::string mode;
	std::string tRunValue;
	std::string newTime = "";
	u8 colorState;

	int timeV;
	int hour;

	TParameter* objRun;
	TParameter* objWRun;
	std::array <ISignal*, 3> container;
	int component = 0;
	int yPos = 0;

public:
	GroupIndicators(int x, int y, u8 colorState, std::string mode, std::string tRun, std::string wRun);
	void view();
	const u16 getHeight(void);
	void valueMode();

	void timeValue();

	bool ProcessMessage(TMessage* m);

	void areaState(unsigned int yPos);

};

