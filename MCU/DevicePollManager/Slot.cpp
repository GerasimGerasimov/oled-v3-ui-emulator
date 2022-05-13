#include "Slot.h"
#include "crc16.h"

Slot::Slot() 
	: Flags(0)
	, onReadEnd(NULL)
	, cmdLen(0){
}

void Slot::init(void) {

}

void Slot::addcmd(u8 cmd[], u8 size) {
	std::memcpy(OutBuf, cmd, size);
	cmdLen = size + 2;
	FrameEndCrc16((u8*)&OutBuf, cmdLen);
}

bool Slot::isReplyValid(s16 result, u8* reply) {
	return (result <= 0)
		   ? false
		   : (bool)(crc16(reply, result) == 0);
}

void Slot::checkRespond(s16 result, u8* reply) {
	(isReplyValid(result, reply))
		? (Flags |= (u16)SlotStateFlags::DATA_VALID)
		: (Flags &= ~(u16)SlotStateFlags::DATA_VALID);
	if (onReadEnd)
		onReadEnd(result, reply);
}

Slot::~Slot() {}

