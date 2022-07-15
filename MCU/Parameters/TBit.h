#ifndef BIT_TYPE_SIGNAL_H
#define BIT_TYPE_SIGNAL_H

#include "stm32f4xx.h"
#include "parameters.h"

class TBit : public TParameter {
public:
	TBit(char* source, int scrLen);
	TBit(TSignalPropsPointers props);
	~TBit();
};

#endif