#include "crc16.h"
#include "bastypes.h"
#include <string>

class ModbusSlave {
public:
	static void getCmdWriteFloatReg();
	static void getCmdWriteU16Reg(u16 reg, u16 value);
	static u16 NumericRegAddrToU16(char* RegAddr);
	static u16 BitRegAddrToU16(char* RegAddr);
	static u16 ByteRegAddrToU16(char* RegAddr);
};