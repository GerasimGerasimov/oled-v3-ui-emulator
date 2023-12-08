#ifndef COM_MASTER_DRIVER_H
#define COM_MASTER_DRIVER_H

#include <string>
#include "stm32f4xx.h"
#include "icommastert.h"
//result >= 0 ����� ������
//result = -1 ������

struct TComMasterTask {
	u8* pbuff;
	u16 len;
	u16 TimeOut;
	TDriverComReadEndHandler callback;
};

struct ComMasterDriver {
public:
	static void open();
	static void send(TComMasterTask task);
	static void close();
private:
	static void com_thread(void);
	static void create_com_thread(void);
	static TDriverComReadEndHandler onReadEnd;
	static u8* outbuf;
	static u16 OutBufLen;
	static u16 TimeOut;
	static u8 reply[256];
        static void onReadData(void);
        static void onTimeOut(void);
};

#endif