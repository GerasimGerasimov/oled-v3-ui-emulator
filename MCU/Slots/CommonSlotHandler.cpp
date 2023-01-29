#include "CommonSlotHandler.h"
#include "utils.h"
#include "modbus.h"
#include "DevicesValuesHandler.h"

static bool isReadCmdGotAnError(u8 cmdcode) {
	return (bool)((cmdcode & 0x80) != 0);
}

void CommonSlotHandler::parseRespond(Slot* slot, u8* reply) {
	/*������� ������ �� ��������� ����, ����� �������� ������ � Device:"U1", Section:"RAM"*/
	/*TODO �������� ����������� ��� ������ ����������. ��� ������ �������� �:
		- ����������� ������������ �� ������ ��������;
		- ������ � �����������;
		- ��������� ������� �����������*/
	//GIST ��� ������������� � throw <T> ������ ��������� � catch (<T> e) ������ ����� ���������� ��������������!
	try {
		if (slot->RespondLenghtOrErrorCode <= 0) throw (int)RespondErrorCodes::LNK;
		if (slot->Flags & (u16)SlotStateFlags::CRC_ERR) throw (int)RespondErrorCodes::CRCE;
		if (isReadCmdGotAnError(reply[(u8)ModbusReadRegsDefs::CMD_POS])) throw (int)RespondErrorCodes::CMD;
		u8 regs_count = reply[(u8)ModbusReadRegsDefs::ANSW_BYTES_POS] >> 1;
		Utils::swp_copy_u16((u8*)&reply[(u8)ModbusReadRegsDefs::ANSW_DATA_POS],
			(u16*)&slot->InputBuf,
			regs_count);
		slot->InputBufValidBytes = regs_count;
		slot->Flags |= (u16)SlotStateFlags::DATA_VALID;
	}
	catch (int e) {
		slot->InputBufValidBytes = 0;
		slot->Flags &= ~(u16)SlotStateFlags::DATA_VALID;
	}
	DevicesValuesHandler::setValues(slot);
}