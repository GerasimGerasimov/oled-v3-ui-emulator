#ifndef SLOT_H
#define SLOT_H

#include <string>
#include <vector>
#include "stm32f4xx.h"
#include "icommastert.h"

#define MB_MASTER_BUF_SIZE  256
#define MB_MASTER_SLOTS_MAX 24

//using TComReadEndHandler = std::function<void(s16 result, u8* reply)>;
enum class SlotStateFlags {
	REPEATING_TRANSMIT = 1,
	SKIP_SLOT = 2,
	TIMEOUT_ERR = 4,
	CRC_ERR = 8,
	DATA_VALID = 16
};

class Slot {
public:
	u16 Flags;
	virtual void init(void);
	void addcmd(u8 cmd[], u8 size);
	void addcmd(const std::vector<u8> &v);
	void checkRespond(s16 result, u8* reply);
	Slot();
	Slot(std::string device, std::string section);
	~Slot();
	u8 cmdLen;
	u8 OutBuf[MB_MASTER_BUF_SIZE];//буфер сообщения для отправки
	u8 InputBuf[MB_MASTER_BUF_SIZE];//буфер сообщения для приёма сообщений  
	TComReadEndHandler onReadEnd;//процедура которая вызывается после получения ответа от устройства, если контрольная сумма сошлась
private:
	std::string Device;
	std::string Section;
	bool isReplyValid(s16 result, u8* reply);
};

#endif