#include "inistring.h"
#include "vars.h"
#include "parameters.h"
#include <parser.h>

typedef struct {
	char* pName;
	char* pComment;
	char* pType;
	char* pOptional;
} TSignalPropsPointers;

static TSignalPropsPointers getSignalProps(const char* source, const int srcLen) {
	TSignalPropsPointers res = {NULL, NULL, NULL, NULL};
	/*�������� ����� ��������� �� ������ "=" �� �������� ����� ��������� (�� ��� ��������� ������)*/
	char* src = (char*) source;
	int size = srcLen;
	//������ ������ ����� � �������� "����" � �����!
	if (IniParser::isDelimimerSizeLimited('=', src, size) != -1) {//����� ���� "="
		res.pName = src;
		if (IniParser::isDelimimerSizeLimited('/', src, size) != -1) {
			res.pComment = src;
			if (IniParser::isDelimimerSizeLimited('/', src, size) != -1) {
				res.pType = src;
				if (IniParser::isDelimimerSizeLimited('/', src, size) != -1) {
					res.pOptional = src;
				}
			}
		}
	}
	return res;
}

pSignal TIniString::getSignal(std::string section, char* source, int scrLen) {
	/*TODO ��� ���� ������� ���������� ������ � �������� ������� vars, word, bit, float � �.�.*/
	TSignalPropsPointers SignalProps = getSignalProps(source, scrLen);
	pSignal s = new TParameter(source, scrLen);
	return s;
}

pSignal TIniString::getScale(std::string section, char* source, int scrLen) {
	/*TODO ��� ���� ������� ���������� ������ � �������� ������� vars, word, bit, float � �.�.*/
	pSignal s = new TScale(source, scrLen);
	return s;
}

