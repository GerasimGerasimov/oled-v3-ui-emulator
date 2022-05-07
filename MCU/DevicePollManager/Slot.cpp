#include "Slot.h"
#include "crc16.h"
#include "com_master_driver.h"

Slot::Slot() 
	: Flags(0)
	, onReadEnd(NULL)
	, cmdLen(0){
}


void Slot::addcmd(u8 cmd[], u8 size) {
	memcpy(OutBuf, cmd, size);
	cmdLen = size + 2;
	FrameEndCrc16((u8*)&OutBuf, cmdLen);
}

void Slot::send(void) {
	//ComMasterDriver::send({ (u8*)&OutBuf, cmdLen, [this](s16 result, u8* reply) {checkRespond(result, reply); } });
}

void Slot::checkRespond(s16 result, u8* reply) {

}

Slot::~Slot() {}

