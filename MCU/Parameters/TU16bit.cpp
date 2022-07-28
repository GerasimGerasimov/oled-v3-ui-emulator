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
	if (ParametersUtils::isAddrInvalid(Addr)) return "err.addr";
	if ((Addr < args.StartAddrOffset)
		|| (Addr > args.LastAddrOffset)) return "out.addr";
	s16 offset = Addr - args.StartAddrOffset;
	bauint raw;
	u8* p = args.InputBuf + offset;
	raw.b[0] = (*p++);
	raw.b[1] = (*p);
	return std::to_string(raw.i);
		/*TODO ���� ��������� ����� �����, �������� ��� ���������� ��������� � ����������� � ������
		��������� �������� � ������� ������ �����, ������� ��� ������ �� ������� � "�����" ��������
		� ����� �� ���������� �����, ������ HEX ��� ���������� (� ����� ������������) ��������*/
	//return "*****";
}
