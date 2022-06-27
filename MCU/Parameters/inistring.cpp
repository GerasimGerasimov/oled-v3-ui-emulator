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
	/*отделить номер параметра со знаком "=" от значащей части параметра (те что разделены слэшем)*/
	char* src = (char*) source;
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

pSignal TIniString::getSignal(std::string section, char* source, int scrLen) {
	/*TODO тут надо парсить переданнюу строку и генерить объекты vars, word, bit, float и т.п.*/
	TSignalPropsPointers SignalProps = getSignalProps(source, scrLen);
	pSignal s = new TParameter(source, scrLen);
	return s;
}

pSignal TIniString::getScale(std::string section, char* source, int scrLen) {
	/*TODO тут надо парсить переданнюу строку и генерить объекты vars, word, bit, float и т.п.*/
	pSignal s = new TScale(source, scrLen);
	return s;
}

