#include "IniSlotsProps.h"
#include "parser.h"

std::map<std::string, TDeviceNetworkProps> IniSlotsProps::Devices = {};

void IniSlotsProps::init(void) {
	readDevices();
}

std::string IniSlotsProps::getSourceOfDev(std::string position) {
	if (Devices.count(position)) {
		std::string s = Devices.at(position).Source;
		return s;
	}
	return "";
}

u16 IniSlotsProps::getDevNetWorkAddr(std::string position) {
	if (Devices.count(position)) {
		u16 a = Devices.at(position).NetworkAddr;
		return a;
	}
	return 0;
}

//"U1":"DEV1/COM1/1/RAM,0x0000,0�0036,0/FLASH,0x2000,0�2069,1000/CD,0xC000,0xC0037,1000/"
//      |    |    | |   |      |      |--����� ����� ��������� �������� (0-������ ����������� � ���� ��������)
//      |    |    | |   |      |-�������� �������
//		|    |    | |   |-��������� �������
//      |    |    | |-�������� ����� (=���� ������ �� DEV1)
//		|    |    |-����� ���������� �� ����
//		|    |-�� ����� UART ���������� ����
//      |-������ �� �������� ��������� ����������

bool IniSlotsProps::readDevices(void) {
	TItemLimits itemLimits = TInternalResources::getItemLimitsByName((char*)"DEVICES");
	if (itemLimits.RootOffset) {
		IniParser::setRoot(itemLimits.RootOffset, itemLimits.Size);
		std::vector<std::string> devices = IniParser::getListOfDelimitedString('/', itemLimits.RootOffset, itemLimits.Size);
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
TDeviceNetworkProps IniSlotsProps::getDeviceNetworkProps(char* src, int size) {
	TDeviceNetworkProps props = { "","",0,{} };
	std::vector<std::string> tmp = IniParser::getListOfDelimitedString('/', src, size);
	props.Source = tmp[0];
	props.COM = tmp[1];
	props.NetworkAddr = std::stoi(tmp[2]);
	std::vector<std::string>::iterator from = (tmp.begin() + 3);
	std::vector<std::string> slotsrawdata (from, tmp.end());
	for (auto& slotstring : slotsrawdata) {
		std::vector<std::string> slotprops = IniParser::getListOfDelimitedString(',', (char*) slotstring.c_str(), slotstring.size());
		//��� ������ �������� ��� ������ ����: RAM,0x0000,0�0036,0, � ����� ������� ����� �� ��������������
		TDeviceSlotProps* slot = new TDeviceSlotProps;
		slot->StartAddr = std::stoi(slotprops[1],0,16);
		slot->LastAddr = std::stoi(slotprops[2],0,16);
		slot->Interval = std::stoi(slotprops[3]);
		props.SlotsMap[slotprops[0]] = slot;
	}
	return props;
}