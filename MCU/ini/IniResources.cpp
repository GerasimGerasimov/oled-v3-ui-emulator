#include "IniResources.h"
#include "parser.h"

const static std::vector<std::string> SectioNameOrder = { "vars", "RAM", "FLASH", "CD"};

const static std::map<std::string, std::string> SectionNameMap = { {"vars","[vars]"}, {"RAM","[RAM]"}, {"FLASH","[FLASH]"},{"CD","[CD]"} };

std::map<std::string, std::map<std::string, std::vector<ISignal* >>> IniResources::Sources = {};
std::map<std::string, TDeviceNetworkProps> IniResources::Devices = {};
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

void IniResources::init(void) {
	readSources();
	readDevices();
}

bool IniResources::readSources(void)
{
	TItemLimits itemLimits = TInternalResources::getItemLimitsByName((char*)"SOURCES");
	if (itemLimits.RootOffset) {
		IniParser::setRoot(itemLimits.RootOffset, itemLimits.Size);
		std::vector<std::string> sources = IniParser::getListOfDelimitedSting('/', itemLimits.RootOffset, itemLimits.Size);
		for (auto& src : sources) {
			itemLimits = TInternalResources::getItemLimitsByName((char*)src.c_str());
			if (itemLimits.RootOffset) {
				IniParser::setRoot(itemLimits.RootOffset, itemLimits.Size);
				/*TODO �������� �������
				��� ������, ����� ������ RAM, FLASH, CD, vars*/
				for (auto& section : SectioNameOrder) {
					std::string value = SectionNameMap.at(section);
					if (IniParser::setSectionToRead((char*)value.c_str())) {
						std::vector<ISignal*> params = {};
						TSectionReadResult readResult = { NULL, 0 };
						while ((readResult = IniParser::getNextTagString()), readResult.result != 0) {
							//TODO ������� ���������� ������ ��������� � ����� � tagSuccess � ��������� �� ������
							ISignal* s = TIniString::getSignal(section, readResult.tag, readResult.result);
							params.push_back(s);
						}
						Sources[src][section] = params;
					}
				}
			}
		}
	}
	return false;
}

//"U1":"DEV1/COM1/1/RAM,0x0000,0�0036,0/FLASH,0x2000,0�2069,1000/CD,0xC000,0xC0037,1000/"
//      |    |    | |   |      |      |--����� ����� ��������� �������� (0-������ ����������� � ���� ��������)
//      |    |    | |   |      |-�������� �������
//		|    |    | |   |-��������� �������
//      |    |    | |-�������� ����� (=���� ������ �� DEV1)
//		|    |    |-����� ���������� �� ����
//		|    |-�� ����� UART ���������� ����
//      |-������ �� �������� ��������� ����������

bool IniResources::readDevices(void) {
	TItemLimits itemLimits = TInternalResources::getItemLimitsByName((char*)"DEVICES");
	if (itemLimits.RootOffset) {
		IniParser::setRoot(itemLimits.RootOffset, itemLimits.Size);
		std::vector<std::string> devices = IniParser::getListOfDelimitedSting('/', itemLimits.RootOffset, itemLimits.Size);
		for (auto& dev : devices) {
			itemLimits = TInternalResources::getItemLimitsByName((char*)dev.c_str());
			if (itemLimits.RootOffset) {
				//������ ������ ���� DEV1/COM1/1/RAM:0/FLASH:1000/CD:1000/
				TDeviceNetworkProps props = getDeviceNetworkProps(itemLimits.RootOffset, itemLimits.Size);
				Devices[dev] = props;
			}
		}
	}
	return false;
}

//"DEV1/COM1/1/RAM,0x0000,0x0036,0,/FLASH,0x2000,0x2069,1000,/CD,0xC000,0xC037,1000,/"
TDeviceNetworkProps IniResources::getDeviceNetworkProps(char* src, int size) {
	TDeviceNetworkProps props = { "","",0,{} };
	std::vector<std::string> tmp = IniParser::getListOfDelimitedSting('/', src, size);
	props.Source = tmp[0];
	props.COM = tmp[1];
	props.NetworkAddr = std::stoi(tmp[2]);
	std::vector<std::string>::iterator from = (tmp.begin() + 3);
	std::vector<std::string> slotsrawdata (from, tmp.end());
	for (auto& slotstring : slotsrawdata) {
		std::vector<std::string> slotprops = IniParser::getListOfDelimitedSting(',', (char*) slotstring.c_str(), slotstring.size());
		//��� ������ �������� ��� ������ ����: RAM,0x0000,0�0036,0, � ����� ������� ����� �� ��������������
		TDeviceSlotProps* slot = new TDeviceSlotProps;
		slot->StartAddr = std::stoi(slotprops[1],0,16);
		slot->LastAddr = std::stoi(slotprops[2],0,16);
		slot->Interval = std::stoi(slotprops[3]);
		props.SlotsMap[slotprops[0]] = slot;
	}
	return props;
}