//служба сообщений
#ifndef CMD_SENDER_H
#define CMD_SENDER_H

#include "stm32f4xx.h"
#include "HandleSubscribers.h"

class CmdSender {
	public:
		static void init(void);
		static void update(const u16 din);
	private:
		static u16 keyStopRun;
		static u16 keyMode;
};

#endif