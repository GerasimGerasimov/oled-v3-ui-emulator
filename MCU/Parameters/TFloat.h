#ifndef FLOAT_TYPE_SIGNAL_H
#define FLOAT_TYPE_SIGNAL_H

#include "stm32f4xx.h"
#include "signal.h"

class TFloat : public ISignal {
public:
	TFloat(char* source, int scrLen);
	TFloat(TSignalPropsPointers props);
	~TFloat();
};

#endif