#ifndef WORD_TYPE_SIGNAL_H
#define WORD_TYPE_SIGNAL_H

#include "stm32f4xx.h"
#include "generalcase.h"

class TU16BIT : public TGeneralCaseSignal {
public:
	TU16BIT(TSignalPropsPointers props);
	~TU16BIT();
private:
	virtual TGenaralCaseRawReturn getRawValue(const TSlotHandlerArsg& args);
};

#endif