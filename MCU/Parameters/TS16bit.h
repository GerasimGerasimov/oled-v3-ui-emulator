#ifndef SIGNED_SHORT_TYPE_SIGNAL_H
#define SIGNED_SHORT_TYPE_SIGNAL_H

#include "stm32f4xx.h"
#include "generalcase.h"

class TS16BIT : public TGeneralCaseSignal {
public:
	TS16BIT(TSignalPropsPointers props);
	~TS16BIT();
	const std::string getValueHex(std::string& src) override;
	TInternalMemAddress getInternalMemAddr();
private:
	virtual TGenaralCaseRawReturn getRawValue(const TSlotHandlerArsg& args);
	s16 string2raw(std::string& src);
};

#endif