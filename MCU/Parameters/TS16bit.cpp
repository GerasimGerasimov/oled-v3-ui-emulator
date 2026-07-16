#include "TS16BIT.h"
#include "bastypes.h"

TS16BIT::TS16BIT(TSignalPropsPointers props)
	: TGeneralCaseSignal (props) {
}

TS16BIT::~TS16BIT(){
}

TGenaralCaseRawReturn TS16BIT::getRawValue(const TSlotHandlerArsg& args) {
	s16 offset = Addr - args.StartAddrOffset;
	u8* p = args.InputBuf + offset;//получил указатель на данные
	bauint raw;//получил два байта данных
	raw.b[0] = (*p++);
	raw.b[1] = (*p);
	TGenaralCaseRawReturn res;
	res.type = TGeneralCaseReturnType::S;
	res.raw.s = raw.s;
	return res;
}

const std::string TS16BIT::getValueHex(std::string& src) {
	s16 value = string2raw(src);

	u16 unsignedValue = (u16)value;
	char s[8];
	//GIST "%.4X" преобразование числа в hex с заданным кол-вом значащих нулей
	sprintf(s, "%.4X", unsignedValue);
	std::string res(s);
	return res;
}

u16 TS16BIT::string2raw(std::string& src) {
	float f = std::stof(src);
	f /= Scale;
	return (s16)f;
}

TInternalMemAddress TS16BIT::getInternalMemAddr() {
	s16 offset = Addr;
	return { offset,2,-1 };
}