#ifndef VARS_H
#define VARS_H

#include "stm32f4xx.h"
#include <vector>
#include <string>

class IScale {
public:
	IScale(char* source, int scrLen);
	~IScale();
};

#endif