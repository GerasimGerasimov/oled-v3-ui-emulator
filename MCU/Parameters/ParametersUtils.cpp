#include "ParametersUtils.h"
#include <parser.h>

s16 ParametersUtils::getByteOffsetFromSlahedAddrStr(char* addr) {
	//������������� �������� - ������ ����� �� �����������!
	//������������ ������� ����� ������ ��� ��������� �������� � ������
	//�.�. ����� = ������������ �������, � ������� ����� ���������� �� 2
	u16 res = 0;
	if (addr) {
		addr++; //�������� ������ � ������� rAAAA, ��� ������������ �"r" �� ��������� ������ ��� ����������� �������������
		std::string s = IniParser::getElement('/', addr);
		try {
			res = std::stoi(s, 0, 16);
			res = (res & 0x00FF) * 2;
		}
		catch (...) {
			res = -1;
		}
	}
	return (s16)res;
}
