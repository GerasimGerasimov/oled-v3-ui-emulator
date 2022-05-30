#ifndef PARAMETERS_H
#define PARAMETERS_H

#include "stm32f4xx.h"
#include <vector>
#include <string>
#include "signal.h"

class TParameter : public ISignal{
public:
	TParameter(char* source, int scrLen);
	~TParameter();
};

#endif