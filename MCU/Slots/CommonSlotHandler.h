#ifndef COMMON_SLOT_HANDLER_H
#define COMMON_SLOT_HANDLER_H
#include "IniSlotsProps.h"
#include "Slot.h"

class CommonSlotHandler {
public:
	static void parseRespond(s16 result, u8* reply);
};

#endif