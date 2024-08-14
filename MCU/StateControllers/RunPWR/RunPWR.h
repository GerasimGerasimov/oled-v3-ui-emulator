#pragma once

#include "stm32f4xx.h"
#include "HandleSubscribers.h"
#include <StateControllers.h>

class RunPWR
{
public:
    static void init();
    static std::map < std::string, TTrackedBit > Tags;
private:
	static void uptate(const std::string PosMem, TSlotHandlerArsg& args);
	static bool checkState();
	static void SlotU1RAMUpdate(TSlotHandlerArsg args);
	static bool State;
};

