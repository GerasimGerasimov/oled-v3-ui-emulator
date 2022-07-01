#ifndef SIGNAL_FACTORY_H
#define SIGNAL_FACTORY_H

#include "stm32f4xx.h"
#include "signal.h"
#include "vars.h"
#include "parameters.h"
#include <vector>
#include <string>

typedef struct {
	char* pName;
	char* pComment;
	char* pType;
	char* pOptional;
} TSignalPropsPointers;

class SignalFactoty {
public:
	static TSignalPropsPointers getSignalProps(const char* source, const int srcLen);
	static pSignal getSignal(TSignalPropsPointers props);
	static pSignal getScale(char* source, int scrLen);
private:
	static pSignal createSignalWORD(TSignalPropsPointers props);
	static pSignal createSignalBit(TSignalPropsPointers props);
};

#endif