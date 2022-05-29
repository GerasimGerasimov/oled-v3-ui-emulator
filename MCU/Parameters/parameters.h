#ifndef PARAMETERS_H
#define PARAMETERS_H

#include "stm32f4xx.h"
#include <vector>
#include <string>

class TParameter : public TIniString {
public:
	TParameter(char* source, int scrLen);
	~TParameter();
};

#endif