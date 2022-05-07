#ifndef DEVICE_POLL_MANAGER_H
#define DEVICE_POLL_MANAGER_H

#include "stm32f4xx.h"
#include "com_master_driver.h"
#include "Slot.h"
#include <vector>

#define MB_MASTER_BUF_SIZE  256
#define MB_MASTER_SLOTS_MAX 24

enum class DevicePollManagerStatus {
	DPMS_WAIT_IDLE = 1,
	DPMS_WAIT_RESPOND = 2
};

class DevicePollManager {
public:
	static void init(void);
	static void execute(void);
	static std::vector <Slot> Slots;
	static u16 Status;
private:
	static void checkRespond(s16 result, u8* reply);
};

#endif