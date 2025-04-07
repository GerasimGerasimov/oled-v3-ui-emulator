#include "Warnings.h"
#include <IniResources.h>
#include <LedWarnings.h>

std::map < std::string, TTrackedBit > Warnings::Tags = {
	{"syncfail", {"U1/RAM/syncfail/", nullptr, false, false}},
	//{"BreakLM19", {"U1/RAM/BreakLM19/", nullptr, false, false}},
	//{"EmergStop", {"U1/RAM/EmergStop/", nullptr, false, false}},
	//{"ExRS485Flt", {"U1/RAM/ExRS485Flt/", nullptr, false, false}},
};

bool Warnings::State = true;

void Warnings::init() {
	for (auto& e : Tags) {
		std::string& tag = (std::string&)e.second.Tag;
		e.second.pBit = (TBit*)IniResources::getSignalByTag(tag);
	}
	HandlerSubscribers::set("U1/RAM/", SlotU1RAMUpdate);
}

void Warnings::uptate(const std::string PosMem, TSlotHandlerArsg& args){
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

bool Warnings::checkState(void) {
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

bool Warnings::isTagInWarning(TTrackedBit& element) {
	return (bool)((element.isValid) && (element.State == false));
}

void Warnings::SlotU1RAMUpdate(TSlotHandlerArsg args) {
	uptate("U1/RAM/", args);
	State = checkState();
	LedWarnings::setState((State?0:1));
}