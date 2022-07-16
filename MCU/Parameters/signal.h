#ifndef ISIGNAL_H
#define ISIGNAL_H

#include "stm32f4xx.h"
#include <vector>
#include <string>

typedef struct {
	char* pName;
	char* pComment;
	char* pType;
	char* pOptional;
} TSignalPropsPointers;


class ISignal {
public:
	ISignal(char* source, int scrLen);
	ISignal(TSignalPropsPointers props);
	~ISignal();
	virtual std::string getName();
	virtual std::string getValue();
protected:
	char* Name;
	char* optional;
};

typedef ISignal* pSignal;

#endif