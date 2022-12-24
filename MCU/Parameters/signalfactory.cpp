#include "signalfactory.h"
#include "parser.h"
#include <map>
#include <functional>
#include "TU8BIT.h"
#include "TU16BIT.h"
#include "TS16Bit.h"
#include "TFloat.h"
#include "TBit.h"
#include "TPrmList.h"

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
	{"TWORD", [](TSignalPropsPointers props) {return new TU16BIT(props); }},
	{"TPrmList", [](TSignalPropsPointers props) {return new TPrmList(props); }}
};

pSignal SignalFactoty::getSignal(const TSignalPropsPointers& props) {
	int size = 100;
	char* _pType = props.pType;
	std::string pType = IniParser::getElement('/', &_pType, size);
	pSignal s = (TypeToSignal.count(pType))
		? TypeToSignal.at(pType)(props)
		: nullptr;
	return s;
}

TScaleProps SignalFactoty::getScaleProps(const char* source, const int srcLen) {
	TScaleProps res = { NULL, NULL, 0};
	/*�������� ����� ��������� �� ������ "=" �� �������� ����� ��������� (�� ��� ��������� ������)*/
	char* src = (char*)source;
	int size = srcLen;
	res.pKey = src;//Name ������������� ������ "="
	if (IniParser::isDelimiterSizeLimited('=', src, size) != -1) {//����� ���� "="
					res.pValue = src;//������ ����� ��� vars ����������� �� /r/n/
					res.ValueSize = size;//������� ����� ������
	}
	return res;
}

pSignal SignalFactoty::getScale (const TScaleProps& props) {
	/*TODO ��� ���� ������� ���������� ������ � �������� ������� vars � ��� ������ �� �������
	  ���� = ��������, �� ������� ���� �������*/
	return new TScale(props);
}