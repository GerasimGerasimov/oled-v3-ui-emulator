#include "TU16BIT.h"
#include "parser.h"

s16 getByteOffsetFromSlahedAddrStr(char* addr) {
	//отрицательное значение - значит адрес не декодирован!
	//используется младшая часть адреса для получения смещения в байтах
	//т.е. адрес = отрасывается префикс, и младшая часть умножается на 2
	u16 res = 0;
	if (addr) {
		addr++; //приходит строка в формате rAAAA, тут передвигаюсь с"r" на следующий символ для правильного декодирования
		std::string s = IniParser::getElement('/', addr);
		try {
			res = std::stoi(s, 0, 16);
			res = (res & 0x00FF) * 2;
		}
		catch (...) {
			res = -1;
		}
	}
	return (s16)res;
}

TU16BIT::TU16BIT(TSignalPropsPointers props)
	: TGeneralCaseSignal(props)
	, Addr(getByteOffsetFromSlahedAddrStr(strAddr)) {
	
}

TU16BIT::~TU16BIT(){
}

std::string TU16BIT::getValue()
{
	if (Addr < 0)
		return "err.addr";
	if (valid) {

	}
	else {
		return "*****";
	}
}
