//служба сообщений
#ifndef CMD_SENDER_H
#define CMD_SENDER_H

#include "stm32f4xx.h"
#include <Slot.h>

class CmdSender {
	public:
		static void init(void);
		static void update(const u16 din);
	private:
		static u16 keyStopReset;
		static u16 keyRun;
		static u16 keyClean;
		static u16 keyVAC;
		static u16 keyPrevStopReset;
		static u16 keyPrevRun;
		static u16 keyPrevClean;
		static u16 keyPrevVAC;
		static bool cmdSendInProcess;
		static u16 TryCnt;
		static void updateKeyRun(const u16 din);
		static void updateKeyStop(const u16 din);
		static void sendCmd(std::string& code);
		static void SlotUpdate(Slot& slot, u8* reply);
};

#endif