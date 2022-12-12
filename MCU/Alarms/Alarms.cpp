#include "Alarms.h"
#include <IniResources.h>
#include <vector>

std::map < std::string, TTrackedBit > Alarms::Tags = {
	{"UbusOK", {"U1/RAM/UbusOK/", nullptr, false, false}},
	//{"UgenOK", {"U1/RAM/UgenOK/", nullptr, false, false}},
	//{"BusUnpwr", {"U1/RAM/BusUnpwr/", nullptr, false, false}},
};

bool Alarms::State = true;
bool Alarms::prevState = true;

void Alarms::init() {
	for (auto& e : Tags) {
		std::string& tag = (std::string&)e.second.Tag;
		e.second.pBit = (TBit*)IniResources::getSignalByTag(tag);
	}
	HandlerSubscribers::set("U1/RAM/", SlotU1RAMUpdate);
}

void Alarms::uptate(const std::string PosMem, TSlotHandlerArsg& args){
	static std::string res = "";
	for (auto& e : Tags) {
		std::string& Tag = (std::string&)e.second.Tag;
		bool isDeviceTag = Tag.find(PosMem) != std::string::npos;
		if (isDeviceTag) {
			TBit* p = e.second.pBit;
			res = p->getValue(args, "");
			if ((res == "0") || (res == "1")) {
				e.second.isValid = true;
				e.second.State = (res == "0") ? true : false; //0-��� ������
			}
			else {
				e.second.isValid = false;
			}
		}
	}
}

bool Alarms::checkState(void) {
	bool res = true;
	for (auto& e : Tags) {
		bool state = e.second.isValid && e.second.State;//���� ��� "1" �� "1", ���� ���-�� "0" �� �� "0"
		if (!state) {//���� ������������ � ���������� "0" ���� ���� ���� �� ��������� "0"
			res = false;
			break;
		}
	}
	return res;
}

void Alarms::openAlarmWindow() {

}

void Alarms::SlotU1RAMUpdate(TSlotHandlerArsg args) {
	uptate("U1/RAM/", args);
	State = Alarms::checkState();
	if (!State && prevState) {
		openAlarmWindow();
		prevState = State;
	}
}