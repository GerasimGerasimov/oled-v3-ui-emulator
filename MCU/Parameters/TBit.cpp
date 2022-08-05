#include "TBit.h"
#include "parser.h"
#include "ParametersUtils.h"
#include "bastypes.h"
//Special case Two
//p13321 = P / C / TBit / xF042 / mask / r2021.1 / 1 / 1 / const / ������ ��� MSU
/*TODO Addr
typedef struct {
	u16 Addr;
	u16 Option;
} TSpecialSignalAddr;
� Addr � ������ ��������� ��������
� � Option - ������ �����, ������� � ���� ����������� ����� �������� ��������
r2021.1 � ����� ���� ������� �����, �� ���� ���� �������� ���������� ����� � ����� ���� �� ��������� �������� ������������ �����.
*/
TBit::TBit(TSignalPropsPointers props)
	: TParameter(props) {
	strAddr = IniParser::getElementPtrByNumber(2, '/', props.pOptional);
	Addr = ParametersUtils::getSpecialAddrForBit(strAddr);	
}

TBit::~TBit(){
}

std::string TBit::getValue(const TSlotHandlerArsg& args, const char* format) {
	std::string res = validation(args);
	return (res != "")
		? res
		: value(args);
}

const std::string TBit::value(const TSlotHandlerArsg& args) {
	bool input = getRawValue(args);
	return (input)?"1":"0";
}

bool TBit::getRawValue(const TSlotHandlerArsg& args) {
	s16 offset = Addr.Addr - args.StartAddrOffset;
	u8* p = args.InputBuf + offset;//������� ��������� �� ������
	bauint raw;//������� ��� ����� ������
	raw.b[0] = (*p++);
	raw.b[1] = (*p);
	bool res = (bool)(raw.i & Addr.Option);
	return res;
}

const std::string TBit::validation(const TSlotHandlerArsg& args) {
	if (args.InputBufValidBytes == 0) return "*";
	if (ParametersUtils::isAddrInvalid(Addr.Addr)) return "err.addr";
	if ((Addr.Addr < args.StartAddrOffset) || (Addr.Addr > args.LastAddrOffset)) return "out.addr";
	return "";
}