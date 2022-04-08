#ifndef EMB_FONTS_H
#define EMB_FONTS_H

#include <stdint.h>

 typedef struct {
     long int code;
     const uint8_t* image;
     const int width;
     const int height;
     } tChar;

 typedef struct {
     int length;
     const tChar *chars;
     } tFont;

#endif