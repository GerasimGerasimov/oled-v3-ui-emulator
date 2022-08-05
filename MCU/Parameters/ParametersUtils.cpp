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

/*� ����� ���� r2021.1/ �������� �����, ���� �������� �������� � ����� ��� ����*/
TSpecialSignalAddr ParametersUtils::getSpecialAddrForBit(char* addr) {
	//������������� �������� - ������ ����� �� �����������!
	//������������ ������� ����� ������ ��� ��������� �������� � ������
	//�.�. ����� = ������������ �������, � ������� ����� ���������� �� 2
	if (addr) {
		try {
			addr++; //�������� ������ � ������� rAAAA.N, ��� ������������ �"r" �� ��������� ������ ��� ����������� �������������
			std::string s = IniParser::getElement('.', addr);
			s16 offset = std::stoi(s, 0, 16);
			offset = (offset & 0x00FF) * 2;
			addr +=5; //�������� � N
			s = IniParser::getElement('/', addr);
			u16 bitnum = std::stoi(s, 0, 16);
			u16 mask  = 1 << bitnum;
			return { offset, mask };
		}
		catch (...) {
			return { -1, 0 };
		}
	}
	return { -1, 0 };
}

/*� ����� ���� r2021.H(L)/ �������� �����, ���� �������� �������� � ����� �����*/
TSpecialSignalAddr ParametersUtils::getSpecialAddrForByte(char* addr) {
	//������������� �������� - ������ ����� �� �����������!
	//������������ ������� ����� ������ ��� ��������� �������� � ������
	//�.�. ����� = ������������ �������, � ������� ����� ���������� �� 2
	if (addr) {
		try {
			addr++; //�������� ������ � ������� rAAAA.H(L), ��� ������������ �"r" �� ��������� ������ ��� ����������� �������������
			std::string s = IniParser::getElement('.', addr);
			s16 offset = std::stoi(s, 0, 16);
			offset = (offset & 0x00FF) * 2;
			addr += 5; //�������� � H/L
			s = IniParser::getElement('/', addr);
			u16 bytenum = (s == "H")
				? 1 : 0;
			return { offset, bytenum };
		}
		catch (...) {
			return { -1, 0 };
		}
	}
	return { -1, 0 };
}

bool ParametersUtils::isAddrInvalid(s16 Addr) {
	return (bool)(Addr < 0);
}

bool ParametersUtils::isAddrValid(s16 Addr) {
	return (bool)(Addr >= 0);
}