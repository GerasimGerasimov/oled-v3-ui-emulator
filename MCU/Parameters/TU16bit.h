#ifndef WORD_TYPE_SIGNAL_H
#define WORD_TYPE_SIGNAL_H

#include "stm32f4xx.h"
#include "signal.h"

class TU16BIT : public ISignal {
public:
	TU16BIT(char* source, int scrLen);
	~TU16BIT();
};

#endif