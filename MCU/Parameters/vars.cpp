#include "vars.h"
#include "parser.h"
#include <vector>

TScale::TScale(char* source, int scrLen) : ISignal(source, scrLen) {
}

TScale::TScale(TScaleProps props)
	: ISignal({NULL, props.pKey, NULL, NULL, props.pValue})
	, ValueSize(props.ValueSize) {
}

TScale::~TScale(){
}

std::string TScale::getName() {
	std::string s = (Name)
		? IniParser::getElement('=', Name)
		: "";
	return s;
}

std::string TScale::getValue() {
	/*��� ���� ������������� ValueSize ��� ��� ������ ����� ���� ��� ������� ���������
	��� � �������� ����� ���������� �������... �������� � � ��� ��� � �������
	� ���� � ������� ����� ������ ���� �������, ������ � �� ���� ������ ��������*/
	std::vector<std::string> sources = IniParser::getListOfDelimitedSting('/', optional, ValueSize);
	/*std::string s = (optional)
		? IniParser::getElement('=', Name)
		: "";
	*/
	return "1.0";
}