#include "CmdSender.h"
#include <IniResources.h>

u16 CmdSender::keyStopReset = 0;
u16 CmdSender::keyRun = 0;
u16 CmdSender::keyClean = 0;
u16 CmdSender::keyVAC = 0;
u16 CmdSender::keyPrevStopReset = 0;
u16 CmdSender::keyPrevRun = 0;
u16 CmdSender::keyPrevClean = 0;
u16 CmdSender::keyPrevVAC = 0;
bool CmdSender::cmdSendInProcess = false;
u16 CmdSender::TryCnt = 3;

static const u16 CMD_RUN = 1111;
static const u16 CMD_STOP = 1000;
static const u16 CMD_RESET = 2222;

static const u16 CMD_NORMAL = 5310;
static const u16 CMD_CLEAN = 5311;
static const u16 CMD_VAC = 5312;
static const u16 CMD_TEST = 5313;

void CmdSender::init() {

}

void CmdSender::update(const u16 din) {
	updateKeyRun(din);
}

void CmdSender::updateKeyRun(const u16 din) {
	keyRun = (din & (1 << 1));
	if (keyPrevRun != keyRun) {
		if (keyRun) {
			if (cmdSendInProcess != true) {
				sendCmd(CMD_RUN);
			}
		}
		keyPrevRun = keyRun;
	}
}

void CmdSender::sendCmd(const u16 cmd) {
	TryCnt = 3;
	cmdSendInProcess = true;
}