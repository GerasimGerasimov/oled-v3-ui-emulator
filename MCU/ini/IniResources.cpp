#include "IniResources.h"
#include "parser.h"

const std::vector<std::string> sections = { "[vars]", "[RAM]", "[FLASH]", "[CD]"};

const std::map<std::string, std::string> msections = { {"vars","[vars]"}, {"RAM","[RAM]"}, {"FLASH","[FLASH]"},{"CD","[CD]"} };
/*TODO ���� ������� ��������� ��� ����� �� ��������� ���������� ������
�� � ���� ������� vars ��������, � ��� �������� CD.. ����� ���� MAP ������� ���������
�������� � �������� �������?*/


std::map<std::string, std::map<std::string, std::vector<ISignal* >>> IniResources::devs = {};
/*TODO ���������� ����� ���������
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

bool IniResources::readSources(void)
{
	TItemLimits itemLimits = TInternalResources::getItemLimitsByName((char*)"SOURCES");
	if (itemLimits.RootOffset) {
		IniParser::setRoot(itemLimits.RootOffset, itemLimits.Size);
		std::vector<std::string> sources = IniParser::getListOfDelimitedSting(itemLimits.RootOffset, itemLimits.Size);
		for (auto& src : sources) {
			itemLimits = TInternalResources::getItemLimitsByName((char*)src.c_str());
			if (itemLimits.RootOffset) {
				IniParser::setRoot(itemLimits.RootOffset, itemLimits.Size);
				/*TODO �������� �������
				��� ������, ����� ������ RAM, FLASH, CD, vars*/
				for (auto& section : msections) {
					if (IniParser::setSectionToRead((char*)section.second.c_str())) {
						std::vector<ISignal*> params = {};
						TSectionReadResult readResult = { NULL, 0 };
						while ((readResult = IniParser::getNextTagString()), readResult.result != 0) {
							//TODO ������� ���������� ������ ��������� � ����� � tagSuccess � ��������� �� ������
							ISignal* s = TIniString::getSignal(section.first, readResult.tag, readResult.result);
							params.push_back(s);
						}
						devs[src][section.first] = params;
					}
				}
			}
		}
	}
	return false;
}

void IniResources::init(void) {
	readSources();
}
