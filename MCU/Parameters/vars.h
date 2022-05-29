#ifndef VARS_H
#define VARS_H

#include "stm32f4xx.h"
#include <vector>
#include <string>
#include "inistring.h"

class IScale : public TIniString {
public:
	IScale(char* source, int scrLen);
	~IScale();
};

#endif