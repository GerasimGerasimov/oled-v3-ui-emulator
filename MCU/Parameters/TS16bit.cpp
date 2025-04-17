#include "TS16BIT.h"
#include "bastypes.h"

TS16BIT::TS16BIT(TSignalPropsPointers props)
	: TGeneralCaseSignal (props) {
}

TS16BIT::~TS16BIT(){
}

const std::string TS16BIT::getValueHex(std::string& src){
	s16 value = string2raw(src);
	char s[5];
	//GIST "%.4X" преобразование числа в hex с заданным кол-вом значащих нулей
	sprintf(s, "%04X", static_cast<uint16_t>(value));
	std::string res(s);
	return res;
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

s16 TS16BIT::string2raw(std::string& src){
	float f = std::stof(src);
	f /= Scale;
	return (s16)f;
}

TInternalMemAddress TS16BIT::getInternalMemAddr() {
	s16 offset = Addr;
	return { offset,2,-1 };
}