#pragma once

#include "stm32f4xx.h"

namespace LedPWR
{
    void init();
    void setState(u16 state);
}