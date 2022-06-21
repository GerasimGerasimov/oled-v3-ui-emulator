#include "CommonSlotHandler.h"
#include "utils.h"

void CommonSlotHandler::parseRespond(Slot& slot, u8* reply) {
	/*������� ������ �� ��������� ����, ����� �������� ������ � Device:"U1", Section:"RAM"*/
	/*TODO ��������� �� ������ ��������� ������*/
	/*TODO ��������� ������ ��������� �� ������, ���� ������ �������*/
	/*TODO �������� ����������� ��� ������ ����������. ��� ������ �������� �:
		- ����������� ������������ �� ������ ��������;
		- ������ � �����������;
		- ��������� ������� �����������*/
	if (slot.Flags & (u16)SlotStateFlags::DATA_VALID) {
		u8 msg_count = reply[2] >> 1;
		swp_copy_u16((u8*)reply[3],
			(u16*)&slot.InputBuf,
			msg_count);
	}
}