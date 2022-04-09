#ifndef T_EMBEDDED_FONTS_H
#define T_EMBEDDED_FONTS_H

#include "stm32f4xx.h"

typedef struct {
	const u16 BytesByWidth;
	const u16 BitsByWidth;
} TCharProps;

struct TEmbeddedFonts {
public:
	static u8 setFont(void);
	static TCharProps setSimbol(u8 Code);
	static bool getBitsLine(u32 &bits);
private:
	static u8 BytesByWidth;
	static u16 ImageSize;
	static u8 ImageHeight;
	static u8 index;
	static u8* CharImage;
};

#endif