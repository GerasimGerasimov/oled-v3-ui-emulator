#ifndef PARAMETERS_H
#define PARAMETERS_H

#include "stm32f4xx.h"
#include <vector>
#include <string>
#include "signal.h"

typedef struct {
	s16 Addr;
	u16 Option;
} TSpecialSignalAddr;

class TParameter : public ISignal{
public:
	TParameter(char* source, int scrLen);
	TParameter(TSignalPropsPointers props);
	~TParameter();
	std::string getComment();
	virtual std::string getMSU();
	virtual void setValueNotValid();
	virtual void setValue();
protected:
	char* Comment;
	char* strAddr;
};

#endif