#include "IniResources.h"
#include "parser.h"

void IniResources::init(void) {
	const std::vector<std::string> devices = {"U1"};
	for (auto & device : devices) {
		TItemLimits itemLimits = TInternalResources::getItemLimitsByName((char*)device.c_str());
		if (itemLimits.RootOffset) {
			IniParser::setRoot(itemLimits.RootOffset, itemLimits.Size);
			/*TODO �������� �������
			��� ������, ����� ������ RAM, FLASH, CD, vars*/
			if (IniParser::setSectionToRead((char*)"[RAM]")) {
				TSectionReadResult readResult = { NULL, 0 };
				while ((readResult = IniParser::getNextTagString()), readResult.result != 0) {
					//TODO ������� ���������� ������ ��������� � ����� � tagSuccess � ��������� �� ������
				}
			}
		}
	}

}