#ifndef BIT_TYPE_SIGNAL_H
#define BIT_TYPE_SIGNAL_H

#include "stm32f4xx.h"
#include "signal.h"

class TBit : public ISignal {
public:
	TBit(char* source, int scrLen);
	TBit(TSignalPropsPointers props);
	~TBit();
};

#endif