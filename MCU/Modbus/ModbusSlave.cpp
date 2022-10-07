#include "ModbusSlave.h"

void ModbusSlave::getCmdWriteFloatReg() {
}

/*на выходе
AD, C, №R(h, l), CW(h, l), CntBytes, Data[0](h, l)..Data[CW](h, l), CRC(h, l)
│   │  │          │          │       │             │                └─(word)crc16
│   │  │          │          │       └─────────────┴─(word)Записываемые данные
│   │  │          │          └─(byte)Кол - во передаваемых байт
│   │  │          └─(word)Кол - во регистров к передаче
│   │  └─(word)Начальный адрес
│   └────(byte)Команда(10h)
└──────(byte)Адрес устройства
*/
void ModbusSlave::getCmdWriteU16Reg(u16 reg, u16 value) {
	/*TODO создание массива команды записи одного регистра*/
}

// rC004 -> 0xC004 (49156)
u16 ModbusSlave::NumericRegAddrToU16(char* RegAddr) {
	std::string s(++RegAddr, 4);
	//GIST преобразование HEX-строки в беззнаковое целое число, основание 16 для HEX
	u16 res = std::stoul(s, nullptr, 16);
	return res;
}

// rC004.D -> 0xC004 (49156)
u16 ModbusSlave::BitRegAddrToU16(char* RegAddr) {
	return 0;
}

// rC004.H -> 0xC004 (49156)
// rC004.L -> 0xC004 (49156)
u16 ModbusSlave::ByteRegAddrToU16(char* RegAddr) {
	return 0;
}