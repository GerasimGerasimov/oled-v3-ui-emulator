#include "IniResources.h"
#include "parser.h"

void IniResources::init(void) {
	const std::vector<std::string> devices = {"U1"};
	for (auto & device : devices) {
		TItemLimits itemLimits = TInternalResources::getItemLimitsByName((char*)device.c_str());
		if (itemLimits.RootOffset) {
			/*TODO �������� �������
			��� ������, ����� ������ RAM, FLASH, CD, vars*/
			IniParser::setRoot(itemLimits.RootOffset, itemLimits.Size);
			char* section = IniParser::SearchSectionBegin((char*)"[vars]");
			IniParser::resetFind(section);
			char* tag = NULL;
			int tagSuccess = 0;
			do {
				tagSuccess = IniParser::getTagString(&tag);
				//������� ���������� �������� � ������ �� �����
				if ((tagSuccess == (int)ParcerResult::END) ||
					(tagSuccess == (int)ParcerResult::SECTION))
					return;
				switch (tagSuccess) {
				case (int)ParcerResult::COMMENT:
					break;
				default:
					tagSuccess = 0;
					/*TODO ������� ���������� ������ ��������� � ����� � tagSuccess � ��������� �� ������ */
					break;
				};
			} while (true);
		}
	}

}