#ifndef T_MCU_FONTS_H
#define T_MCU_FONTS_H

#include <string>
#include <map>
#include "stm32f4xx.h"
#include "emb_fonts.h"

typedef tFont* pMCUFont;

struct TMCUFonts {
	public:
		static void init(void);
		static pMCUFont getFont(std::string name);
		static std::map<std::string, pMCUFont > fonts;
};

#endif