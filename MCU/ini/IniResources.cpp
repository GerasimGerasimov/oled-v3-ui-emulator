#include "IniResources.h"
#include "parser.h"

void IniResources::init(void) {
	const std::vector<std::string> inis = {"U1"};
	//INI - именно такую запись будем парсить, U1 чтобы сгенерить ошибку. Потом все ini для парсинга будут называться Ux
	const TItemLimits itemLimits = TInternalResources::getItemLimitsByName((char*)inis[0].c_str());
	if (itemLimits.RootOffset) {
		/*TODO осталось парсить
		как обычно, найти секции RAM, FLASH, CD, vars
		*/
		IniParser::setRoot(itemLimits.RootOffset, itemLimits.Size);
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