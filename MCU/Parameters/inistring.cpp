#include "inistring.h"
#include "vars.h"
#include "parameters.h"

pSignal TIniString::getSignal(std::string section, char* source, int scrLen) {
	/*TODO ��� ���� ������� ���������� ������ � �������� ������� vars, word, bit, float � �.�.*/
	pSignal s = new ISignal(source, scrLen);
	return s;
}

