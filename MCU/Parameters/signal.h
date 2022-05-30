#ifndef ISIGNAL_H
#define ISIGNAL_H

#include "stm32f4xx.h"
#include <vector>
#include <string>

class ISignal {
public:
	ISignal(char* source, int scrLen);
	~ISignal();
};

typedef ISignal* pSignal;

#endif