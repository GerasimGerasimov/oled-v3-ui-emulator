#include "IniResources.h"
#include "parser.h"

void IniResources::init(void) {
	const std::vector<std::string> inis = {"U1"};
	//INI - именно такую запись будем парсить, U1 чтобы сгенерить ошибку. Потом все ini для парсинга будут называться Ux
	const pItem ini = TInternalResources::getItemByName((char*) inis[0].c_str());
	if (ini) {
		u32 Offset = ini->BinaryDataAddr;
		u32 Size = ini->BinaryDataSize;
		/*TODO осталось парсить
		как обычно, найти секции RAM, FLASH, CD, vars
		*/
		char* Root = TInternalResources::getRoot() + Offset;
		IniParser::setRoot(Root, Size);
		char* section = IniParser::SearchSectionBegin((char*)"[vars]");
		IniParser::resetFind(section);
		char* tag = NULL;
		int tagSuccess = 0;
		do {
			tagSuccess = IniParser::getTagString(&tag);
			//условия завершения парсинга и выхода из цикла
			if ((tagSuccess == (int)ParcerResult::END) ||
				(tagSuccess == (int)ParcerResult::SECTION))
				return;
			switch (tagSuccess) {
				case (int)ParcerResult::COMMENT:
					break;
				default:
					tagSuccess = 0;
					/*TODO парсить полученную строку используя её длину в tagSuccess и указатель на начало */
					break;
			};
		} while (true);
	}
}