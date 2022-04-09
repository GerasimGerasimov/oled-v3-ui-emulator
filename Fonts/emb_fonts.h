#ifndef EMB_FONTS_H
#define EMB_FONTS_H

#include <stdint.h>

 typedef struct {
     const int code;
     const uint8_t* image;
     const int width;
     } tChar;

 typedef struct {
     const int length;
     const int height;
     const tChar *chars;
     } tFont;

#endif