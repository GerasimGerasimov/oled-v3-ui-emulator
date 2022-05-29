#include "IniResources.h"
#include "parser.h"

const std::vector<std::string> sections = { "[vars]", "[RAM]", "[FLASH]", "[CD]"};
std::map<std::string, std::map<std::string, std::vector<TIniString*>>> IniResources::devs = {};
/*TODO обеспечить такую структуру
U1
 |-vars
 |   |-S1=
 |
 |-RAM
 |   |-p0=
 |
 |-FLASH
 |-CD
*/


void IniResources::init(void) {
	const std::vector<std::string> devices = {"U1"};
	for (auto & device : devices) {
		TItemLimits itemLimits = TInternalResources::getItemLimitsByName((char*)device.c_str());
		if (itemLimits.RootOffset) {
			IniParser::setRoot(itemLimits.RootOffset, itemLimits.Size);
			/*TODO осталось парсить
			как обычно, найти секции RAM, FLASH, CD, vars*/
			for (auto& section : sections) {
				if (IniParser::setSectionToRead((char*)section.c_str())) {
					std::vector<TIniString*> params = {};
					TSectionReadResult readResult = { NULL, 0 };
					while ((readResult = IniParser::getNextTagString()), readResult.result != 0) {
						//TODO парсить полученную строку используя её длину в tagSuccess и указатель на начало
						TIniString* p = new TIniString(section, readResult.tag, readResult.result);
						params.push_back(p);
					}
					devs[device][section] = params;
				}
			}
		}
	}

}