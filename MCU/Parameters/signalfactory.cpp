#include "signalfactory.h"
#include "parser.h"
#include <map>

TSignalPropsPointers SignalFactoty::getSignalProps(const char* source, const int srcLen) {
	TSignalPropsPointers res = { NULL, NULL, NULL, NULL };
	/*отделить номер параметра со знаком "=" от значащей части параметра (те что разделены слэшем)*/
	char* src = (char*)source;
	int size = srcLen;
	//пускай строки будут с символом "слэш" в конце!
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

pSignal SignalFactoty::createSignalWORD(TSignalPropsPointers props) {
	return NULL;
}

pSignal SignalFactoty::createSignalBit(TSignalPropsPointers props) {
	return NULL;
}

static pSignal createSignalWORD(TSignalPropsPointers props) {
	return NULL;
}

static pSignal createSignalBit(TSignalPropsPointers props) {
	return NULL;
}

const static const std::map<std::string, createSignal> TypeToSignal = {
	{"TBit",  createSignalBit},
	{"TWORD", createSignalWORD}
};


pSignal SignalFactoty::getSignal(TSignalPropsPointers props) {
	/*TODO тут надо парсить переданнюу строку и генерить объекты vars, word, bit, float и т.п.*/
	//props.pType - это ссылка на строку, которая оканчивается на "/" слэш
	int size = 100;
	std::string pType = IniParser::getElement('/', &props.pType, size);

	//if (pType == "TWORD") {}
	return (TypeToSignal.count(pType))
		? TypeToSignal.at(pType)(props)
		: NULL;

}

pSignal SignalFactoty::getScale (char* source, int scrLen) {
	/*TODO тут надо парсить переданнюу строку и генерить объекты vars а они бывают от простых
	  ключ = значение, до сложных типа списков*/
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