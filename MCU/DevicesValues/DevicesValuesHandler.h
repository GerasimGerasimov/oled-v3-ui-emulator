#ifndef DEVICES_VALUES_HANDLER_H
#define DEVICES_VALUES_HANDLER_H
#include "IniSlotsProps.h"
#include "Slot.h"

class DevicesValuesHandler {
	/*TODO ���������� ������ ����� � �������� ����������*/
public:
	static void setValues(Slot& slot);
	static void setDefault(Slot& slot);
};

#endif