#ifndef SIGNAL_FACTORY_H
#define SIGNAL_FACTORY_H

#include "stm32f4xx.h"
#include "signal.h"
#include "vars.h"
#include "parameters.h"
#include <vector>
#include <string>

class SignalFactoty {
public:
	static TSignalPropsPointers getSignalProps(const char* source, const int srcLen);
	static TSignalPropsPointers getScaleProps(const char* source, const int srcLen);
	static pSignal getSignal(TSignalPropsPointers props);
	static pSignal getScale(TSignalPropsPointers props);
};

#endif