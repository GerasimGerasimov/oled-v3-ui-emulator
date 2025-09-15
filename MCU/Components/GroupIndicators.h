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
	u8 colorState;

	int timeV;
	int hour;

	TParameter* objRun;
	TParameter* objWRun;

	std::array <ISignal*, 2> container;
public:
	GroupIndicators(int x, int y, u8 colorState, std::string mode, std::string tRun, std::string wRun);
	void view();
	const u16 getHeight(void);
	void valueMode();

};

