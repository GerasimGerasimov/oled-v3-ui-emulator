#include "inistring.h"
#include "vars.h"
#include "parameters.h"

pSignal TIniString::getSignal(std::string section, char* source, int scrLen) {
	/*TODO тут надо парсить переданнюу строку и генерить объекты vars, word, bit, float и т.п.*/
	pSignal s = new ISignal(source, scrLen);
	return s;
}

