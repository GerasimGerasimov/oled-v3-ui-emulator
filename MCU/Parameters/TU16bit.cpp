#include "TU16BIT.h"
#include "parser.h"
#include "ParametersUtils.h"
#include "bastypes.h"

static const u16 TU16BIT_DATA_SIZE = 2;

TU16BIT::TU16BIT(TSignalPropsPointers props)
	: TGeneralCaseSignal(props)
	, Addr(ParametersUtils::getByteOffsetFromSlahedAddrStr(strAddr)) {
	
}

TU16BIT::~TU16BIT(){
}

std::string TU16BIT::getValue(TSlotHandlerArsg args)
{
	std::string res = validation(args);
	return (res != "")
		? res
		: value(args);
}

std::string TU16BIT::value(TSlotHandlerArsg args) {
	s16 offset = Addr - args.StartAddrOffset;
	//получил указатель на данные
	u8* p = args.InputBuf + offset;
	//получил два байта данных
	bauint raw = { };
	raw.b[0] = (*p++);
	raw.b[1] = (*p);
	//как-то перевёл в строку.
	return std::to_string(raw.i);
	/*TODO зная начальный адрес слота, смещение при нормальной адресации и размерность в байтах
	вычислить смещение в массиве данных слота, забрать эти данные из массива в "сырое" значение
	и далее по требованию юзера, выдать HEX или Физическое (с учтом коэффициента) значение*/
}

std::string TU16BIT::validation(TSlotHandlerArsg args) {
	if (args.InputBufValidBytes == 0) return "***.**";
	if (ParametersUtils::isAddrInvalid(Addr)) return "err.addr";
	if ((Addr < args.StartAddrOffset) || (Addr > args.LastAddrOffset)) return "out.addr";
	return "";
}