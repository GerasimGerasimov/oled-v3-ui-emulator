#ifndef COM_MASTER_DRIVER_H
#define COM_MASTER_DRIVER_H

#include <string>
#include "stm32f4xx.h"
#include <windows.h>
#include "icommastert.h"
//result >= 0 ����� ������
//result = -1 ������

struct TComMasterTask {
	u8* pbuff;
	u16 len;
	u16 DelayAfterWrite;
	TDriverComReadEndHandler callback;
};

struct ComMasterDriver {
public:
	static void open();
	static void send(TComMasterTask task);
	static void close();
private:
	static HANDLE hCom;
	static HANDLE hComThread;
	static DWORD  dwComThreadId;
	static DWORD WINAPI com_thread(LPVOID lpParam);
	static void create_com_thread(void);
	static TDriverComReadEndHandler onReadEdnd;
	static u8* outbuf;
	static u16 OutBufLen;
	static u16 DelayAfterWrite;
	static u8 reply[256];
};

#endif