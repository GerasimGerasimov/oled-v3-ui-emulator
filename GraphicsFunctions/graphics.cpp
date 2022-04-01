#include "graphics.h"
#include <iostream>

u8 TGrahics::screen[128][64];

void TGrahics::setPixel(TPixel& props) {
	screen[props.x][props.y] = props.color;
}

void TGrahics::setPixel(u8 x, u8 y, u8 color) {
    screen[x][y] = color;
}

void TGrahics::Line(u8 X1, u8 Y1, u8 X2, u8 Y2, u8 Color) {
    int deltaX = abs(X2 - X1);
    int deltaY = abs(Y2 - Y1);
    int signX = X1 < X2 ? 1 : -1;
    int signY = Y1 < Y2 ? 1 : -1;
    int error = deltaX - deltaY;
    int error2;

    for (;;)
    {
        setPixel(X1, Y1, Color);
        if (X1 == X2 && Y1 == Y2)
            break;

        error2 = error * 2;

        if (error2 > -deltaY)
        {
            error -= deltaY;
            X1 += signX;
        }

        if (error2 < deltaX)
        {
            error += deltaX;
            Y1 += signY;
        }
    }
}
