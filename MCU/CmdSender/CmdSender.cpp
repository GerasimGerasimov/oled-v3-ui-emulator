#include "CmdSender.h"
#include <AppModbusSlave.h>

u16 CmdSender::keyStopReset = 0;
u16 CmdSender::keyRun = 0;
u16 CmdSender::keyClean = 0;
u16 CmdSender::keyVAC = 0;
u16 CmdSender::keyPrevStopReset = 0;
u16 CmdSender::keyPrevRun = 0;
u16 CmdSender::keyPrevClean = 0;
u16 CmdSender::keyPrevVAC = 0;
bool CmdSender::cmdSendInProcess = false;
u16 CmdSender::TryCount = 3;

/*TODO c Clean VAC сложнее, это переключатель
в котором если не Clean и не VAC, то NORMAL*/

static const std::string CMD_RUN = "1111";
static const std::string CMD_STOP = "1000";
static const std::string CMD_RESET = "2222";

static const std::string CMD_NORMAL = "5310";
static const std::string CMD_CLEAN = "5311";
static const std::string CMD_VAC = "5312";
static const std::string CMD_TEST = "5313";

void CmdSender::init() {

}

void CmdSender::update(const u16 din) {
	updateKeyRun(din);
	updateKeyStop(din);
}

void CmdSender::updateKeyStop(const u16 din) {
	keyStopReset = (din & (1 << 0));
	if (keyPrevStopReset != keyStopReset) {
		if (keyStopReset) {
			if (cmdSendInProcess != true) {
				/*TODO если в Аварии то послать команду RESET*/
				sendCmd((std::string&)CMD_STOP);
			}
		}
		keyPrevStopReset = keyStopReset;
	}
}

void CmdSender::updateKeyRun(const u16 din) {
	keyRun = (din & (1 << 1));
	if (keyPrevRun != keyRun) {
		if (keyRun) {
			if (cmdSendInProcess != true) {
				sendCmd((std::string&) CMD_RUN);
			}
		}
		keyPrevRun = keyRun;
	}
}

void CmdSender::sendCmd(std::string& code) {
	std::string cmd = "U1/RAM/CMD/";
	TryCount = 3;
	cmdSendInProcess = true;
	ModbusSlave::setValue(cmd, code, SlotUpdate);
}

void CmdSender::SlotUpdate(Slot& slot, u8* reply) {
	if (slot.RespondLenghtOrErrorCode) {
		slot.Flags |= (u16)SlotStateFlags::SKIP_SLOT;
		cmdSendInProcess = false;
	}
	else {
		if (TryCount)
			TryCount--;
		else {
			slot.Flags |= (u16)SlotStateFlags::SKIP_SLOT;
			cmdSendInProcess = false;
		}
	}
	/*TODO разделить использование слота с PageEditValue*/
}