#include "ParametersUtils.h"
#include <parser.h>

s16 ParametersUtils::getByteOffsetFromSlahedAddrStr(char* addr) {
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
