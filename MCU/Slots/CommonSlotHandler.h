#ifndef COMMON_SLOT_HANDLER_H
#define COMMON_SLOT_HANDLER_H
#include "IniSlotsProps.h"
#include "Slot.h"

class CommonSlotHandler {
public:
	static void parseRespond(Slot* slot, u8* reply);//u8* reply ��� �� ���������� � ����! ��� �������� ������,
	                                                //��� ��� ��������� ���������, �������� swap ���������� ������ ��� 0�03 ������� ������
};

#endif