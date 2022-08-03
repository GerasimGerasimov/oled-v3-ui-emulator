#ifndef USBYTE_TYPE_SIGNAL_H
#define USBYNE_TYPE_SIGNAL_H

#include "stm32f4xx.h"
#include "generalcase.h"

class TU8BIT : public TParameter {
public:
	TU8BIT(TSignalPropsPointers props);
	~TU8BIT();
	virtual std::string getValue();
private:
	TSpecialSignalAddr Addr;
};

#endif