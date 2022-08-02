#ifndef WORD_TYPE_SIGNAL_H
#define WORD_TYPE_SIGNAL_H

#include "stm32f4xx.h"
#include "generalcase.h"

class TU16BIT : public TGeneralCaseSignal {
public:
	TU16BIT(TSignalPropsPointers props);
	~TU16BIT();
	virtual std::string getValue(const TSlotHandlerArsg& args, const char* format);
private:
	s16 Addr;
	float Scale;
	std::string validation(const TSlotHandlerArsg& args);
	std::string value(const TSlotHandlerArsg& args, const char* format);
	float getScaleFromProps(const char* dev);
	float scale();
};

#endif