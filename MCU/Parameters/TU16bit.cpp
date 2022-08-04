#include "TU16BIT.h"
#include "bastypes.h"

TU16BIT::TU16BIT(TSignalPropsPointers props)
	: TGeneralCaseSignal(props) {
}

TU16BIT::~TU16BIT(){
}

TGenaralCaseRawReturn TU16BIT::getRawValue(const TSlotHandlerArsg& args) {
	s16 offset = Addr - args.StartAddrOffset;
	u8* p = args.InputBuf + offset;//получил указатель на данные
	bauint raw;//получил два байта данных
	raw.b[0] = (*p++);
	raw.b[1] = (*p);
	TGenaralCaseRawReturn res;
		res.type = TGeneralCaseReturnType::U;
		res.raw.i = raw.i;
	return res;
}

