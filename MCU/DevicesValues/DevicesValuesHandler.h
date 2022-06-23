#ifndef DEVICES_VALUES_HANDLER_H
#define DEVICES_VALUES_HANDLER_H
#include "IniSlotsProps.h"
#include "Slot.h"

class DevicesValuesHandler {
	/*TODO превратить данные слота в значнеия параметров*/
public:
	static void setValues(Slot& slot);
	static void setDefault(Slot& slot);
};

#endif