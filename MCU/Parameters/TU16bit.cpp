#include "TU16BIT.h"
#include "parser.h"
#include "ParametersUtils.h"
#include "bastypes.h"
#include "scaleutils.h"
#include "Utils.h"

TU16BIT::TU16BIT(TSignalPropsPointers props)
	: TGeneralCaseSignal(props)
	, Addr(ParametersUtils::getByteOffsetFromSlahedAddrStr(strAddr)) 
	, Scale(ScaleUtils::getScaleFromProps(props.dev, props.pOptional)) {
}

TU16BIT::~TU16BIT(){
}

std::string TU16BIT::getValue(const TSlotHandlerArsg& args, const char* format)
{
	std::string res = validation(args);
	return (res != "")
		? res
		: value(args, format);
}

std::string TU16BIT::value(const TSlotHandlerArsg& args, const char* format) {
	float res = getRawValue(args) * scale();
	return Utils::getValueAsFormatStr(res, format);
}

u16 TU16BIT::getRawValue(const TSlotHandlerArsg& args) {
	s16 offset = Addr - args.StartAddrOffset;
	u8* p = args.InputBuf + offset;//получил указатель на данные
	bauint raw;//получил два байта данных
	raw.b[0] = (*p++);
	raw.b[1] = (*p);
	return raw.i;
}

std::string TU16BIT::validation(const TSlotHandlerArsg& args) {
	if (args.InputBufValidBytes == 0) return "***.**";
	if (ParametersUtils::isAddrInvalid(Addr)) return "err.addr";
	if ((Addr < args.StartAddrOffset) || (Addr > args.LastAddrOffset)) return "out.addr";
	return "";
}

float TU16BIT::scale() {
	return Scale;
}