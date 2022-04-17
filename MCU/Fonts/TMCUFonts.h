#ifndef T_MCU_FONTS_H
#define T_MCU_FONTS_H

#include <string>
#include <map>
#include "stm32f4xx.h"
#include "emb_fonts.h"

typedef tFont* pMCUFont;

struct TTextSizes {
	u16 width;
	u16 height;
};

struct TMCUFonts {
	public:
		static void init(void);
		static pMCUFont getFont(std::string name);
		static TTextSizes getTextSizes(std::string text, std::string FontName);
		static std::map<std::string, pMCUFont > fonts;
};

#endif