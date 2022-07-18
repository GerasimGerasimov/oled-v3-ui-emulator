#include "TU16BIT.h"
#include "parser.h"
#include "ParametersUtils.h"

TU16BIT::TU16BIT(TSignalPropsPointers props)
	: TGeneralCaseSignal(props)
	, Addr(ParametersUtils::getByteOffsetFromSlahedAddrStr(strAddr)) {
	
}

TU16BIT::~TU16BIT(){
}

std::string TU16BIT::getValue()
{
	if (Addr < 0)
		return "err.addr";
	if (valid) {
		/*TODO зная начальный адрес слота, смещение при нормальной адресации и размерность в байтах
		вычислить смещение в массиве данных слота, забрать эти данные из массива в "сырое" значение
		и далее по требованию юзера, выдать HEX или Физическое (с учтом коэффициента) значение*/
	}
	else {
		return "*****";
	}
}

void TU16BIT::setValue() {
	valid = true;
}