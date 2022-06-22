#include "CommonSlotHandler.h"
#include "utils.h"

#define MODBUS_CMD_POSITION 1
#define MODBUS_READ_BYTES_POSITION 2
#define MODBUS_READ_DATA_POSITION 3

static bool isReadCmdNotValid(u8 cmdcode) {
	return (bool)((cmdcode & 0x80) != 0);
}

void CommonSlotHandler::parseRespond(Slot& slot, u8* reply) {
	/*������� ������ �� ��������� ����, ����� �������� ������ � Device:"U1", Section:"RAM"*/
	/*TODO �������� ����������� ��� ������ ����������. ��� ������ �������� �:
		- ����������� ������������ �� ������ ��������;
		- ������ � �����������;
		- ��������� ������� �����������*/
	//GIST ��� ������������� � throw <T> ������ ��������� � catch (<T> e) ������ ����� ���������� ��������������!
	try {
		if (slot.RespondLenghtOrErrorCode <= 0) throw -1;
		if (slot.Flags & (u16)SlotStateFlags::CRC_ERR) throw -2;
		if (isReadCmdNotValid(reply[MODBUS_CMD_POSITION])) throw -3;
		u8 regs_count = reply[MODBUS_READ_BYTES_POSITION] >> 1;
		swp_copy_u16((u8*)&reply[MODBUS_READ_DATA_POSITION],
			(u16*)&slot.InputBuf,
			regs_count);
		slot.Flags |= (u16)SlotStateFlags::DATA_VALID;
	}
	catch (int e) {
		slot.Flags &= ~(u16)SlotStateFlags::DATA_VALID;
	}
}