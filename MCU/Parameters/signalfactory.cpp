#include "signalfactory.h"
#include "parser.h"
#include <map>
#include "TU16BIT.h"

TSignalPropsPointers SignalFactoty::getSignalProps(const char* source, const int srcLen) {
	TSignalPropsPointers res = { NULL, NULL, NULL, NULL };
	/*�������� ����� ��������� �� ������ "=" �� �������� ����� ��������� (�� ��� ��������� ������)*/
	char* src = (char*)source;
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


pSignal SignalFactoty::createSignalWORD(TSignalPropsPointers props) {
	return NULL;
}

pSignal SignalFactoty::createSignalBit(TSignalPropsPointers props) {
	return NULL;
}

typedef pSignal(*createSignal)(TSignalPropsPointers props);

pSignal SignalFactoty::getSignal(TSignalPropsPointers props) {
	/*TODO ��� ���� ������� ���������� ������ � �������� ������� vars, word, bit, float � �.�.*/
	//props.pType - ��� ������ �� ������, ������� ������������ �� "/" ����
	int size = 100;
	std::string pType = IniParser::getElement('/', &props.pType, size);
	/*GIST �� ������ ������ ������������ ������ ������� �� �������.
	�������� ��������� ������������� ��� � ������� ��� ��� (��� �������) ������ ������� � ������������ �������,
	�������� �� ��������� �� ����� ���[���] = �����*/
	const std::map<std::string, createSignal> TypeToSignal = {
		{"TBit",  SignalFactoty::createSignalBit},
		{"TWORD", SignalFactoty::createSignalWORD}
	};

	//if (pType == "TWORD") {}
	return (TypeToSignal.count(pType))
		? TypeToSignal.at(pType)(props)
		: NULL;

}

pSignal SignalFactoty::getScale (char* source, int scrLen) {
	/*TODO ��� ���� ������� ���������� ������ � �������� ������� vars � ��� ������ �� �������
	  ���� = ��������, �� ������� ���� �������*/
	return new TScale(source, scrLen);
}

/*
	private factory (ini: string): TSignal {
		const ObjType = this.getObjTypeFromIni(ini);
		const ObjTypes = {
			'TBit'  : () => {return new TBit(ini, this.vars)},
			'TWORD' : () => {return new TU16(ini, this.vars)},
			'TByte' : () => {return new TU8(ini, this.vars)},
			'TInteger' : () => {return new TS16(ini, this.vars)},
			'TFloat'   : () => {return new TF32(ini, this.vars)},
		'default': () = > {
			console.log(`${ObjType} not found`)
				return undefined;
					}
				}
				return (ObjTypes[ObjType] || ObjTypes['default'])()
			}

*/