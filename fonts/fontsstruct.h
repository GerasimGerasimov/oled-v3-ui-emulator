#ifndef FONTSSTRUCT_H
#define FONTSSTRUCT_H
#include "stm32f4xx.h"

typedef struct 
{
  const u8 widthBits;
  const u16 offset;
}FONT_CHAR_INFO;


typedef struct
{
  	const u8 CharHeight;    // Character height in bits (Verdana12pt = 21 bit height)
	const char StartChar;   // Start character, example '!'  
	const char EndChar;     // End character, example  '~', 
	const u8 SpaceWidth;     // Width, in pixels, of space character, example  2, 
	const FONT_CHAR_INFO* charInfo; // pointer to Character descriptor array (pointer to array of char information)
	const u8* data;    // pointer to Character bitmap array pointer to generated (array of character visual representation)
} FONT_INFO;

#endif