#ifndef SIGNED_SHORT_TYPE_SIGNAL_H
#define SIGNED_SHORT_TYPE_SIGNAL_H

#include "stm32f4xx.h"
#include "parameters.h"

class TS16BIT : public TParameter {
public:
	TS16BIT(char* source, int scrLen);
	TS16BIT(TSignalPropsPointers props);
	~TS16BIT();
};

#endif