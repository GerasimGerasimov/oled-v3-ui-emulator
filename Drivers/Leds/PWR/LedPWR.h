#pragma once

#include "stm32f4xx.h"
#include <Windows.h>

class LedPWR
{
public:
    static void init(HWND hWndMain);
    static void setState(u16 state);
private:
    static HWND hwnd;
    static HDC hdc;
    static RECT rect;
    static HBRUSH GREEN_BRUSH;
};

