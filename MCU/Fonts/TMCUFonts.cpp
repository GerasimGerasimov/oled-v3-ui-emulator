#include "TMCUFonts.h"
#include <MSSansSerifBold14.cpp>
#include <Verdana12.cpp>

std::map<std::string, pMCUFont> TMCUFonts::fonts = std::map<std::string, pMCUFont>();

void TMCUFonts::init(void) {
	fonts["MSSansSerifBold14"] = (pMCUFont) &MSSansSerifBold14;
	fonts["Verdana12"] = (pMCUFont) &Verdana12;
}

pMCUFont TMCUFonts::getFont(std::string name) {
	return fonts[name];
}

TTextSizes TMCUFonts::getTextSizes(std::string text, std::string FontName) {
	pMCUFont font = fonts[FontName];
	u16 height = font->height;
	u16 width = 0;
	for (u8 code : text) {
		width += font->chars[code].width;
	}
	return { width, height };
}