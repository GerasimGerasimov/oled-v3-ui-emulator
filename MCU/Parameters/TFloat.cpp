#include "TFloat.h"
#include "bastypes.h"
#include "Utils.h"


TFloat::TFloat(TSignalPropsPointers props)
	: TGeneralCaseSignal(props) {
	
}

TFloat::~TFloat(){
}

//x3EC1B08A 0,3783
std::string TFloat::value(const TSlotHandlerArsg& args, const char* format) {
	TGenaralCaseRawReturn input = getRawValue(args);
	float res = input.raw.f * Scale;
	/*������ ������ ��� TFloat � ���������� ������� ������*/
	return Utils::getValueAsFormatStr(res, Utils::getFloatFormat(res));
}

TGenaralCaseRawReturn TFloat::getRawValue(const TSlotHandlerArsg& args) {
	s16 offset = Addr - args.StartAddrOffset;
	u8* p = args.InputBuf + offset;//������� ��������� �� ������
	baulong  raw;//������� ��� ����� ������
	raw.b[0] = (*p++);
	raw.b[1] = (*p++);
	raw.b[2] = (*p++);
	raw.b[3] = (*p);
	TGenaralCaseRawReturn res;
	res.type = TGeneralCaseReturnType::F;
	res.raw.f = raw.f;
	return res;
}

const std::string TFloat::getValueHex(std::string& src) {
	u32 value = string2raw(src);
	char s[10];
	//GIST "%.4X" �������������� ����� � hex � �������� ���-��� �������� �����
	sprintf(s, "%.8X", value);
	std::string res(s);
	return res;
}

u32 TFloat::string2raw(std::string& src) {
	float f = std::stof(src);
	f /= Scale;
	u32 i;
	memcpy(&i, &f, 4);
	return i;
}

TInternalMemAddress TFloat::getInternalMemAddr() {
	s16 offset = Addr;
	return { offset,4,-1 };
}