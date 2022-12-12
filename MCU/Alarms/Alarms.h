//������ ���������
#ifndef ALARMS_H
#define ALARMS_H

#include "stm32f4xx.h"
#include <map>
#include <string>
#include "TBit.h"
#include "HandleSubscribers.h"

typedef struct TTrackedBit {
	const std::string Tag;
	TBit* pBit;
	bool isValid;
	bool State;
};

class Alarms {
	public:
		static void init(void);
		static bool isAlarmOnce(void);
		static std::map < std::string, TTrackedBit > Tags;
	private:
		static void uptate(const std::string PosMem, TSlotHandlerArsg& args);
		static bool checkState(void);
		static void SlotU1RAMUpdate(TSlotHandlerArsg args);
		static bool State;
		static bool prevState;
};

#endif