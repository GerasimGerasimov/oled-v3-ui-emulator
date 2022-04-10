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
