#include "TEmbeddedFonts.h"
#include <MSSansSerifBold14.cpp>

u8 TEmbeddedFonts::BytesByWidth = 0;
u8 TEmbeddedFonts::index = 0;
u8* TEmbeddedFonts::CharImage = NULL;
u16 TEmbeddedFonts::ImageSize = 0;
u8 TEmbeddedFonts::ImageHeight = 0;

u8 TEmbeddedFonts::setFont(void) {
	ImageHeight = MSSansSerifBold14.height;
	return ImageHeight;
}

TCharProps TEmbeddedFonts::setSimbol(u8 Code) {
	u16 width = MSSansSerifBold14.chars[Code].width;
	CharImage = (u8 *) MSSansSerifBold14.chars[Code].image;
	index = 0;
	BytesByWidth = (width / 8) + ((width % 8 == 0) ? 0 : 1);
	ImageSize = BytesByWidth * ImageHeight;
	return { BytesByWidth , width };
}

bool TEmbeddedFonts::getBitsLine(u32& bits) {
	if (index != ImageSize) {
		bits = 0;
		u8 i = BytesByWidth;
		while (i-- != 0) {
			bits = bits << 8;
			bits |= CharImage[index++];
		}
		return true;
	}
	else
		return false;
}
