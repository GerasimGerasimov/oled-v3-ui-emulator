#ifndef FLOAT_TYPE_SIGNAL_H
#define FLOAT_TYPE_SIGNAL_H

#include "stm32f4xx.h"
#include "parameters.h"

class TFloat : public TParameter {
public:
	TFloat(char* source, int scrLen);
	TFloat(TSignalPropsPointers props);
	~TFloat();
};

#endif