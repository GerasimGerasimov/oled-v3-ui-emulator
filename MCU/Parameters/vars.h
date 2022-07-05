#ifndef VARS_H
#define VARS_H

#include "stm32f4xx.h"
#include <vector>
#include <string>
#include "signal.h"

class TScale : public ISignal {
public:
	TScale(char* source, int scrLen);
	TScale(TSignalPropsPointers props);
	~TScale();
protected:
	std::string getName();
};

#endif