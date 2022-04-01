#include "display_driver.h"
#include <iostream>

HDC TDisplayDriver::dc = NULL;

void TDisplayDriver::setDC(HDC _dc) {
	dc = _dc;
}

//#define VIEW_PORT_MAX_WIDTH  128 //ширина
//#define VIEW_PORT_MAX_HEIGHT 64  //высота

void TDisplayDriver::out(void) {
    RECT r;
    COLORREF color = 0;
    for (int y = 0; y < VIEW_PORT_MAX_HEIGHT; y++) {
        for (int x = 0; x < VIEW_PORT_MAX_WIDTH; x++) {
            color = (TGrahics::screen[x][y] != 0)
                ? LIGHT_COLOR
                : EPMTY_COLOR;
            r.left = x * DISPLAY_DRRIVER_SCALE;
            r.top = y * DISPLAY_DRRIVER_SCALE;
            r.right = r.left + DISPLAY_DRRIVER_SCALE;
            r.bottom = r.top + DISPLAY_DRRIVER_SCALE;
            HBRUSH br = CreateSolidBrush(color);
            FillRect(dc, &r, br);
            DeleteObject(br);

        }
    }
};