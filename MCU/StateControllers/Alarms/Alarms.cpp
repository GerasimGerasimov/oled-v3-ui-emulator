#include "Alarms.h"
#include <IniResources.h>
#include "LedAlarms.h"

/*TODO добавлять к аварии метку последовательности срабатываения 1,2,3 и т.д.
если аварий нет, то счётчик последовательностей сбрасывается. готовясь к новому "циклу"*/

/*TODO зная номер последовательности срабатывания (далее "НПС") (с меньшим номером сработала раньше)
при выводе на PageAlarms сортировать аварии по возрастанию НПС, т.е. первая сработавшая авария
будет первой в списке и т.д.*/

/*TODO когда "раскачаю RTC (по полной, с окном установки времени) то к аварии добавить метку времени"*/
std::map < std::string, TTrackedBit > Alarms::Tags = {
	{"FAULT", {"U1/RAM/FAULT/", nullptr, false, false, false}},
	{"GlobalError", {"U1/RAM/GlobalError/", nullptr, false, false, false}},
	{"FSAsyncRun", {"U1/RAM/FSAsyncRun/", nullptr, false, false, false}},
	{"AsyncRun", {"U1/RAM/AsyncRun/", nullptr, false, false, false}},
	{"FieldFail", {"U1/RAM/FieldFail/", nullptr, false, false, false}},
	{"IExcMaxFlt", {"U1/RAM/IExcMaxFlt/", nullptr, false, false, false}},
	{"IttMaxFlt", {"U1/RAM/IttMaxFlt/", nullptr, false, false, false}},
	{"MPSFlt", {"U1/RAM/MPSFlt/", nullptr, false, false, false}},
	{"R_INSL_FLT", {"U1/RAM/R_INSL_FLT/", nullptr, false, false, false}},
	{"stFreqDwnFltEnable", {"U1/RAM/stFreqDwnFltEnable/", nullptr, false, false, false}},
	{"FreqMinFlt", {"U1/RAM/FreqMinFlt/", nullptr, false, false, false}},
	{"IttAsymFlt", {"U1/RAM/IttAsymFlt/", nullptr, false, false, false}},
	{"FreqMinFltTime", {"U1/RAM/FreqMinFltTime/", nullptr, false, false, false}},
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
				e.second.State = (res == "0") ? true : false; //0-нет аварий
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
		// Убираем привязку к имени "FAULT". Проверяем абсолютно ВСЕ аварии в карте!
		bool valid = e.second.isValid;
		bool state = e.second.State; // true - норма, false - авария

		if (valid) {
			if (!state) { // Если State == false, значит зафиксирована авария
				res = true;
				break; // Одной аварии достаточно, чтобы зажечь светодиод. Выходим из цикла.
			}
		}
	}
	return res;
}

bool Alarms::isAlarmOnce(void) {
	bool stateChanged = false;

	for (auto& e : Tags) {
		bool currentAlarmState = (e.second.isValid && !e.second.State);

		if (currentAlarmState != e.second.prevState) {
			stateChanged = true; 

			e.second.prevState = currentAlarmState;
		}
	}
	return stateChanged;
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