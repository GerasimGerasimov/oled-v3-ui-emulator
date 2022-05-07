#include "DevicePollManager.h"
#include "crc16.h"
#include "consolelog.h"

static Slot SlotU1RAM;

std::vector <Slot> DevicePollManager::Slots = {SlotU1RAM};
u16 DevicePollManager::Status = (u16)DevicePollManagerStatus::DPMS_WAIT_IDLE;
static u8 cmd[] = { 1, 17 };

void DevicePollManager::init(void) {
	SlotU1RAM.Flags |= (u16)SlotStateFlags::SSF_SKIP_SLOT;
	SlotU1RAM.addcmd(cmd, sizeof(cmd));
}

void DevicePollManager::execute(void) {
	switch ((DevicePollManagerStatus)Status)
	{
	case DevicePollManagerStatus::DPMS_WAIT_IDLE: {
				Slot* s = &SlotU1RAM;
				ComMasterDriver::send({ (u8*)&s->OutBuf, s->cmdLen, {checkRespond} });
				Status = (u16)DevicePollManagerStatus::DPMS_WAIT_RESPOND;
			}
			break;
		case DevicePollManagerStatus::DPMS_WAIT_RESPOND:
			break;
		default:
			break;
	}

}

void DevicePollManager::checkRespond(s16 result, u8* reply) {
	if (result < 0) {
		console::log(L"comcallback:Error\n");
	}
	else {
		std::string str((char*)reply, (int)result);
		str += "\n";
		std::wstring wstr(str.begin(), str.end());
		console::log(wstr);
	}
}