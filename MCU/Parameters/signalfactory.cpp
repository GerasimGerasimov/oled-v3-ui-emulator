#include "signalfactory.h"
#include "parser.h"
#include <map>
#include <functional>
#include "TU16BIT.h"
#include "TS16Bit.h"
#include "TFloat.h"
#include "TBit.h"

TSignalPropsPointers SignalFactoty::getSignalProps(const char* source, const int srcLen) {
	TSignalPropsPointers res = { NULL, NULL, NULL, NULL };
	/*отделить номер параметра со знаком "=" от значащей части параметра (те что разделены слэшем)*/
	char* src = (char*)source;
	int size = srcLen;
	//строки будут с символом "слэш" в конце!
	if (IniParser::isDelimimerSizeLimited('=', src, size) != -1) {//нашёл знак "="
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

typedef pSignal(*createSignal)(TSignalPropsPointers props);

pSignal SignalFactoty::getSignal(TSignalPropsPointers props) {
	int size = 100;
	std::string pType = IniParser::getElement('/', &props.pType, size);
	/*GIST создание объеата из словаря*/
	const std::map<std::string, std::function<pSignal(TSignalPropsPointers)>> TypeToSignal = {
		{"TFloat", [](TSignalPropsPointers props) {return new TFloat(props); }},
		{"TInteger", [](TSignalPropsPointers props) {return new TS16BIT(props); }},
		{"TBit", [](TSignalPropsPointers props) {return new TBit(props); }},
		{"TWORD", [](TSignalPropsPointers props) {return new TU16BIT(props); }}
	};
	pSignal s = (TypeToSignal.count(pType))
		? TypeToSignal.at(pType)(props)
		: NULL;
	return s;
}

pSignal SignalFactoty::getScale (char* source, int scrLen) {
	/*TODO тут надо парсить переданнюу строку и генерить объекты vars а они бывают от простых
	  ключ = значение, до сложных типа списков*/
	return new TScale(source, scrLen);
}