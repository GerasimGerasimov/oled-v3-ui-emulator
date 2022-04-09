#include "graphics.h"
#include <iostream>
#include "TEmbeddedFonts.h"

u8 TGrahics::screen[128][64];

void TGrahics::setPixel(TPixel& props) {
	screen[props.x][props.y] = props.color;
}

void TGrahics::setPixel(u8 x, u8 y, u8 color) {
    screen[x][y] = color;
}

void TGrahics::outText(std::string text, u16 x, u16 y, u16 color) {
    u16 height = TEmbeddedFonts::setFont();
    for (auto& code : text) {
        putChar(code, x, y, color);
    }
}

void TGrahics::putChar(u8 Code, u16& x, u16 y, u16 color) {
    TCharProps CharProps = TEmbeddedFonts::setSimbol(Code);
    u16 bitsCnt = 0;
    u32 bits = 0;
    u16 start_x = x;
    u32 mask = (1 << (CharProps.BytesByWidth * 8 - 1));
    while (TEmbeddedFonts::getBitsLine(bits)) {
        if (y >= VIEW_PORT_MAX_HEIGHT) continue;
        bitsCnt = CharProps.BitsByWidth;
        x = start_x;
        while (bitsCnt--) {
            if (x >= VIEW_PORT_MAX_WIDTH) continue;
            if ((bits & mask) == 0) {
                setPixel(x, y, color);
            }
            bits <<= 1;
            x++;
        }
        y++;
    };
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
