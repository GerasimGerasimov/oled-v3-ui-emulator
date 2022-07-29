#include "TU16BIT.h"
#include "parser.h"
#include "ParametersUtils.h"
#include "bastypes.h"

#define _CRT_SECURE_NO_WARNINGS

static const u16 TU16BIT_DATA_SIZE = 2;

TU16BIT::TU16BIT(TSignalPropsPointers props)
	: TGeneralCaseSignal(props)
	, Addr(ParametersUtils::getByteOffsetFromSlahedAddrStr(strAddr)) {
	
}

TU16BIT::~TU16BIT(){
}

std::string TU16BIT::getValue(TSlotHandlerArsg args, const char* format)
{
	std::string res = validation(args);
	return (res != "")
		? res
		: value(args, format);
}



std::string TU16BIT::value(TSlotHandlerArsg args, const char* format) {
	s16 offset = Addr - args.StartAddrOffset;
	//������� ��������� �� ������
	u8* p = args.InputBuf + offset;
	//������� ��� ����� ������
	bauint raw = { };
	raw.b[0] = (*p++);
	raw.b[1] = (*p);
	//���-�� ������ � ������.
	float res = raw.i * scale();
	
	/*TODO ����� ���������� ������, ������� ������ ����� �������*/
	//"%.2f";
	int size = std::snprintf(nullptr, 0, format , res);
	std::string output(size + 1, '\0');
	std::sprintf(&output[0], format, res);
	return output;

	//return std::to_string(raw.i);
}

std::string TU16BIT::validation(TSlotHandlerArsg args) {
	if (args.InputBufValidBytes == 0) return "***.**";
	if (ParametersUtils::isAddrInvalid(Addr)) return "err.addr";
	if ((Addr < args.StartAddrOffset) || (Addr > args.LastAddrOffset)) return "out.addr";
	return "";
}

float TU16BIT::scale() {
	return 1.0f;
}