#ifndef PARAMETERS_UTILS_H
#define PARAMETERS_UTILS_H

#include "stm32f4xx.h"
#include <vector>
#include <string>

class ParametersUtils {
public:
	static s16 getByteOffsetFromSlahedAddrStr(char* addr);
};

#endif