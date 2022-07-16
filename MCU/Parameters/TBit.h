#ifndef BIT_TYPE_SIGNAL_H
#define BIT_TYPE_SIGNAL_H

#include "stm32f4xx.h"
#include "parameters.h"

class TBit : public TParameter {
public:
	TBit(TSignalPropsPointers props);
	~TBit();
private:
	TSpecialSignalAddr Addr;
};

#endif