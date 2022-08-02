#include "signalfactory.h"
#include "parser.h"
#include <map>
#include <functional>
#include "TU8BIT.h"
#include "TU16BIT.h"
#include "TS16Bit.h"
#include "TFloat.h"
#include "TBit.h"

TSignalPropsPointers SignalFactoty::getSignalProps(const char* dev, const char* source, const int srcLen) {
	TSignalPropsPointers res = { NULL, NULL, NULL, NULL, NULL };
	res.dev = (char*) dev;
	/*�������� ����� ��������� �� ������ "=" �� �������� ����� ��������� (�� ��� ��������� ������)*/
	char* src = (char*)source;
	int size = srcLen;
	//������ ����� � �������� "����" � �����!
	if (IniParser::isDelimiterSizeLimited('=', src, size) != -1) {//����� ���� "="
		res.pName = src;
		if (IniParser::isDelimiterSizeLimited('/', src, size) != -1) {
			res.pComment = src;
			if (IniParser::isDelimiterSizeLimited('/', src, size) != -1) {
				res.pType = src;
				if (IniParser::isDelimiterSizeLimited('/', src, size) != -1) {
					res.pOptional = src;
				}
			}
		}
	}
	return res;
}

static const std::map<std::string, std::function<pSignal(TSignalPropsPointers)>> TypeToSignal = {
	{"TByte", [](TSignalPropsPointers props) {return new TU8BIT(props); }},
	{"TFloat", [](TSignalPropsPointers props) {return new TFloat(props); }},
	{"TInteger", [](TSignalPropsPointers props) {return new TS16BIT(props); }},
	{"TBit", [](TSignalPropsPointers props) {return new TBit(props); }},
	{"TWORD", [](TSignalPropsPointers props) {return new TU16BIT(props); }}
};

pSignal SignalFactoty::getSignal(const TSignalPropsPointers& props) {
	int size = 100;
	char* _pType = props.pType;
	std::string pType = IniParser::getElement('/', &_pType, size);
	pSignal s = (TypeToSignal.count(pType))
		? TypeToSignal.at(pType)(props)
		: NULL;
	return s;
}

TSignalPropsPointers SignalFactoty::getScaleProps(const char* source, const int srcLen) {
	TSignalPropsPointers res = { NULL, NULL, NULL, NULL };
	/*�������� ����� ��������� �� ������ "=" �� �������� ����� ��������� (�� ��� ��������� ������)*/
	char* src = (char*)source;
	int size = srcLen;
	res.pName = src;//Name ������������� ������ "="
	if (IniParser::isDelimiterSizeLimited('=', src, size) != -1) {//����� ���� "="
					res.pOptional = src;//������ ����� ��� vars ����������� �� /r/n/
	}
	return res;
}

pSignal SignalFactoty::getScale (const TSignalPropsPointers& props) {
	/*TODO ��� ���� ������� ���������� ������ � �������� ������� vars � ��� ������ �� �������
	  ���� = ��������, �� ������� ���� �������*/
	return new TScale(props);
}