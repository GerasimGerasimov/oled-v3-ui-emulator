#ifndef SLOT_H
#define SLOT_H

#include "stm32f4xx.h"
#include "com_master_driver.h"

#define MB_MASTER_BUF_SIZE  256
#define MB_MASTER_SLOTS_MAX 24

//using TComReadEndHandler = std::function<void(s16 result, u8* reply)>;
enum class SlotStateFlags {
	SSF_REPEATING_TRANSMIT = 1,
	SSF_SKIP_SLOT = 2,
	SSF_TIMEOUT_ERR = 4,
	SSF_CRC_ERR = 8
};

class Slot {
public:
	u16 Flags;
	void addcmd(u8 cmd[], u8 size);
	void send(void);
	void checkRespond(s16 result, u8* reply);
	Slot();
	~Slot();
	u8 cmdLen;
	u8 OutBuf[MB_MASTER_BUF_SIZE];//буфер сообщения для отправки
	u8 InputBuf[MB_MASTER_BUF_SIZE];//буфер сообщения для приёма сообщений  
private:
	TComReadEndHandler onReadEnd;//процедура которая вызывается после получения ответа от устройства, если контрольная сумма сошлась
};

#endif