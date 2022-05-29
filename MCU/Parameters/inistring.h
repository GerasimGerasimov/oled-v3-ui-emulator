#ifndef INISTRING_H
#define INISTRING_H

#include "stm32f4xx.h"
#include <vector>
#include <string>

class TIniString {
public:
	TIniString(std::string section, char* source, int scrLen);
	~TIniString();
};

#endif