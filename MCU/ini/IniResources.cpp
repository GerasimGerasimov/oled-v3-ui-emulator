#include "IniResources.h"
#include "parser.h"

void IniResources::init(void) {
	const std::vector<std::string> inis = {"U1"};
	//INI - именно такую запись будем парсить, U1 чтобы сгенерить ошибку. ѕотом все ini дл€ парсинга будут называтьс€ Ux
	const pItem ini = TInternalResources::getItemByName((char*) inis[0].c_str());
	if (ini) {
		u32 Offset = ini->BinaryDataAddr;
		u32 Size = ini->BinaryDataSize;
		/*TODO осталось парсить
		как обычно, найти секции RAM, FLASH, CD, vars
		*/
		char* Root = TInternalResources::getRoot() + Offset;
		IniParser::setRoot(Root, Size);
		//int lines = IniParser::getSectionLinesCount((char*)"[RAM]");
		char* section = IniParser::SearchSectionBegin((char*)"[RAM]");
		char* start = section;
		IniParser::resetFind(start);
		char* tag = NULL;
		int tagSuccess = 0;
		do {
			tagSuccess = IniParser::getTagString(&tag);
			//tag = 0;
		} while (true);
	}
}