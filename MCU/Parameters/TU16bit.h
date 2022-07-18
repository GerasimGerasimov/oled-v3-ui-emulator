#ifndef WORD_TYPE_SIGNAL_H
#define WORD_TYPE_SIGNAL_H

#include "stm32f4xx.h"
#include "generalcase.h"

class TU16BIT : public TGeneralCaseSignal {
public:
	TU16BIT(TSignalPropsPointers props);
	~TU16BIT();
	virtual std::string getValue();
	virtual void setValue();
private:
	s16 Addr;
};

#endif