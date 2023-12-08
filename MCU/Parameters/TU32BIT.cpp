#include "TU32BIT.h"
#include "bastypes.h"

TU32BIT::TU32BIT(TSignalPropsPointers props) : TGeneralCaseSignal(props) {}


const std::string TU32BIT::getValueHex(std::string& src) {
	u32 value = string2raw(src);
	char s[10];
	//GIST "%.4X" преобразование числа в hex с заданным кол-вом значащих нулей
	sprintf(s, "%.8X", value);
	std::string res(s);
	return res;
}

TInternalMemAddress TU32BIT::getInternalMemAddr() {
	s16 offset = Addr;
	return { offset,4,-1 };
}

TGenaralCaseRawReturn TU32BIT::getRawValue(const TSlotHandlerArsg& args) {
	s16 offset = Addr - args.StartAddrOffset;
	u8* p = args.InputBuf + offset;//получил указатель на данные
	baulong  raw;//получил 4 байта данных
	raw.b[0] = (*p++);
	raw.b[1] = (*p++);
	raw.b[2] = (*p++);
	raw.b[3] = (*p);
	TGenaralCaseRawReturn res;
	res.type = TGeneralCaseReturnType::U;
	res.raw.i = raw.i;
	return res;
}

u32 TU32BIT::string2raw(std::string& src) {
	float f = std::stof(src);
	f /= Scale;
	return static_cast<u32>(f);
}
