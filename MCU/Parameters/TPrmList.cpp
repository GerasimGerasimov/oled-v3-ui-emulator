#include "TPrmList.h"
#include "parser.h"
#include "ParametersUtils.h"
#include "bastypes.h"
#include "scaleutils.h"
#include "Utils.h"

TPrmList::TPrmList(TSignalPropsPointers props)
	: TParameter(props)
	, MSU (IniParser::getElementPtrByNumber(2, '/', props.pOptional)) {
	strAddr = IniParser::getElementPtrByNumber(1, '/', props.pOptional);
	Addr = ParametersUtils::getSpecialAddrForByte(strAddr);
	Scale = ScaleUtils::getScaleFromProps(props.dev, props.pOptional);
}

TPrmList::~TPrmList(){
}

std::string TPrmList::getMSU()
{
	return (MSU)
		? IniParser::getElement('/', MSU)
		: "";
}

void TPrmList::setValue() {}

//p501=RS485_1_BPS/Baudrate/TPrmList/xF001/r2000.H/BPS//x01#9600/x02#19200/x03#57600/x04#115200/x04/

std::string TPrmList::getValue(const TSlotHandlerArsg& args, const char* format) {
	std::string res = validation(args);
	return (res != "")
		? res
		: value(args, format);
}

const std::string TPrmList::value(const TSlotHandlerArsg& args, const char* format) {
	u8 input = getRawValue(args);
	//����� 7-� ����
	// [7+0]            [7+1]                [7+N]
	// /index0#data0#ai0/index1#data1#ai1/.../indexN#dataN#aiN/Base/
	// �ase ���������� ���, ��� � �� ��� ������� '#'
	char* options = optional;//���������� ��������� ��������� ��� ��� ����� ���� ������ ���
	char* plist = IniParser::getElementPtrByNumber(4, '/', options);
	char* listAddr = plist;//���������� ��������� ��������� ��� ��� ����� ���� ������ ���
	int size = IniParser::getStringLenght(&listAddr);
	std::vector<std::string> list = IniParser::getListOfDelimitedString('/', plist, size);
	//������ �������
	//����������� ������ ���� x01#9600, ���� �������� ����� �� # (��� x01 �������� ��� � input)
	//� ���� �������, �� ������� ������ ����� #, ��� � ����� ���������
	for (auto& e : list) {
		int index = e.find('#');
		if (index == std::string::npos) continue;
		u8 firstentry = (e[0] == 'x') ? 1 : 0;
		e[index] = 0;//����� ������
		int value = std::stoi(&e.c_str()[firstentry], 0, 16);
		if (value == input) {
			std::string res = std::string(e, index + 1);
			return res;
		}
	}
	return "?";
}

u8 TPrmList::getRawValue(const TSlotHandlerArsg& args) {
	s16 offset = Addr.Addr - args.StartAddrOffset;
	u8* p = args.InputBuf + offset;//������� ��������� �� ������
	bauint raw;//������� ��� ����� ������
	raw.b[0] = (*p++);
	raw.b[1] = (*p);
	u8 res = (Addr.Option == 1)? raw.b[1] : raw.b[0];
	return res;
}

const std::string TPrmList::validation(const TSlotHandlerArsg& args) {
	if (args.InputBufValidBytes == 0) return "?";
	if (ParametersUtils::isAddrInvalid(Addr.Addr)) return "err.addr";
	if ((Addr.Addr < args.StartAddrOffset) || (Addr.Addr > args.LastAddrOffset)) return "out.addr";
	return "";
}