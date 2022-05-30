#ifndef INISTRING_H
#define INISTRING_H

#include "stm32f4xx.h"
#include <vector>
#include <string>
#include "signal.h"

class TIniString {
public:
	static pSignal getSignal(std::string section, char* source, int scrLen);
};

#endif