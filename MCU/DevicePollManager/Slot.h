#ifndef SLOT_H
#define SLOT_H

#include <string>
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
	void checkRespond(s16 result, u8* reply);
	Slot();
	~Slot();
	u8 cmdLen;
	u8 OutBuf[MB_MASTER_BUF_SIZE];//����� ��������� ��� ��������
	u8 InputBuf[MB_MASTER_BUF_SIZE];//����� ��������� ��� ����� ���������  
	TComReadEndHandler onReadEnd;//��������� ������� ���������� ����� ��������� ������ �� ����������, ���� ����������� ����� �������
private:
	bool isReplyValid(s16 result, u8* reply);
};

#endif