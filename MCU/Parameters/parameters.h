#ifndef PARAMETERS_H
#define PARAMETERS_H

#include "stm32f4xx.h"
#include <vector>
#include <string>

class IParameter {
public:
	IParameter(char* source, int scrLen);
	~IParameter();
};

#endif