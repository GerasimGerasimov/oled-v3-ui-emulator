#pragma once

#include "generalcase.h"

class TU32BIT : public TGeneralCaseSignal {
public:
	TU32BIT(TSignalPropsPointers props);
	const std::string getValueHex(std::string& src);
	TInternalMemAddress getInternalMemAddr();
private:
	virtual TGenaralCaseRawReturn getRawValue(const TSlotHandlerArsg& args);
	u32 string2raw(std::string& src);
};

