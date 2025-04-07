#include "Alarms.h"
#include <IniResources.h>
#include "LedAlarms.h"

/*TODO ��������� � ������ ����� ������������������ ������������� 1,2,3 � �.�.
���� ������ ���, �� ������� ������������������� ������������. �������� � ������ "�����"*/

/*TODO ���� ����� ������������������ ������������ (����� "���") (� ������� ������� ��������� ������)
��� ������ �� PageAlarms ����������� ������ �� ����������� ���, �.�. ������ ����������� ������
����� ������ � ������ � �.�.*/

/*TODO ����� "�������� RTC (�� ������, � ����� ��������� �������) �� � ������ �������� ����� �������"*/
std::map < std::string, TTrackedBit > Alarms::Tags = {
	{"InMtzAlm", {"U1/RAM/InMtzAlm/", nullptr, false, false}},
	{"OutMtzAlm", {"U1/RAM/OutMtzAlm/", nullptr, false, false}},
	{"OverloadAlm", {"U1/RAM/OverloadAlm/", nullptr, false, false}},
	{"IinAsymAlm", {"U1/RAM/IinAsymAlm/", nullptr, false, false}},
	{"UinAsymAlm", {"U1/RAM/UinAsymAlm/", nullptr, false, false}},
	{"UinFailAlm", {"U1/RAM/UinFailAlm/", nullptr, false, false}},
	{"SyncFailAlm", {"U1/RAM/SyncFailAlm/", nullptr, false, false}},
	{"UoutMinAlm", {"U1/RAM/UoutMinAlm/", nullptr, false, false}},
	{"UoutMaxAlm", {"U1/RAM/UoutMaxAlm/", nullptr, false, false}},
	{"StartFailAlm", {"U1/RAM/StartFailAlm/", nullptr, false, false}},
	{"eStopAlm", {"U1/RAM/eStopAlm/", nullptr, false, false}},
	{"OpenDoorAlm", {"U1/RAM/OpenDoorAlm/", nullptr, false, false}},
	{"ToverheatAlm", {"U1/RAM/ToverheatAlm/", nullptr, false, false}},
};

bool Alarms::State = true;
u8 Alarms::UppedFlags = 0;
u8 Alarms::PrevUppedFlags = 0;

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
	bool res = false;
	for (auto& e : Tags) {
		bool valid = e.second.isValid;
		bool state = e.second.State;//���� ��� "1" �� "1", ���� ���-�� "0" �� �� "0"
		if (valid) {//������ �������
			if (!state) {//���� ������������ � ���������� "0" ���� ���� ���� �� ��������� "0"
				res = true;
				break;
			}
		}
		else {//���-�� �� �������� ��������
			res = false;
			break;
		}
	}
	return res;
}

bool Alarms::isAlarmOnce(void) {
	bool res = false;
	UppedFlags = 0;
	for (auto& e : Tags) {
		bool state = (bool)((e.second.isValid == true) && (e.second.State == false));//���� ��� "1" �� "1", ���� ���-�� "0" �� �� "0"
		if (state) {//���� ������������ � ���������� "0" ���� ���� ���� �� ��������� "0"
			UppedFlags++;
		}
	}
	res = (bool)(PrevUppedFlags != UppedFlags);
	PrevUppedFlags = UppedFlags;
	return res;
}

bool Alarms::isTagAlarmed(TTrackedBit& element) {
	return (bool)((element.isValid) && (element.State == false));
}

void Alarms::SlotU1RAMUpdate(TSlotHandlerArsg args) {
	uptate("U1/RAM/", args);
	State = checkState();
	LedAlarms::setState((State?1:0));
}

bool Alarms::isAlarm(void) {
	return State;
}