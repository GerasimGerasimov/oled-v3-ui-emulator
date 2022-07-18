#ifndef GENERAL_CASE_H
#define GENERAL_CASE_H

#include "stm32f4xx.h"
#include <vector>
#include <string>
#include "parameters.h"

class TGeneralCaseSignal : public TParameter{
public:
	TGeneralCaseSignal(TSignalPropsPointers props);
	~TGeneralCaseSignal();
	std::string getMSU();
	virtual void setValue();
protected:
	char* MSU;
};

#endif