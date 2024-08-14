#include "LedPWR.h"
#include "resource.h"

HWND LedPWR::hwnd = nullptr;
HDC LedPWR::hdc = nullptr;
RECT LedPWR::rect = {0,0,0,0};
HBRUSH LedPWR::GREEN_BRUSH = CreateSolidBrush(RGB(0, 255, 0));

const int border = 3;

void LedPWR::init(HWND hWndMain){
	hwnd = GetDlgItem(hWndMain, ID_BUTTON_PWR);
	hdc = GetDC(hwnd);
	bool res = GetClientRect(hwnd, &rect);
	rect.left += border;
	rect.right -= border;
	rect.top += border;
	rect.bottom -= border;
	setState(1);
}

void LedPWR::setState(u16 state){
	switch(state){
	case 0:
		FillRect(hdc, &rect, (HBRUSH)GetStockObject(WHITE_BRUSH));
		break;
	case 1:
		FillRect(hdc, &rect, GREEN_BRUSH);
		break;
	};
}
