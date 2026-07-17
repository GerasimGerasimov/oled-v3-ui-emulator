#include "Warnings.h"
#include <IniResources.h>
#include <LedWarnings.h>

std::map < std::string, TTrackedBit > Warnings::Tags = {
	{"R_INSL_LOW", {"U1/RAM/R_INSL_LOW/", nullptr, false, false, false}},
	{"i2tR", {"U1/RAM/i2tR/", nullptr, false, false, false}},
	{"UstLow", {"U1/RAM/UstLow/", nullptr, false, false, false}},
	{"UstFail", {"U1/RAM/UstFail/", nullptr, false, false, false}},
	{"SlideCirctErr", {"U1/RAM/SlideCirctErr/", nullptr, false, false, false}},
	{"MMS_Error", {"U1/RAM/MMS_Error/", nullptr, false, false, false}},
	{"DExS_PWR_LNK", {"U1/RAM/DExS_PWR_LNK/", nullptr, false, false, false}},
	{"SyncRect", {"U1/RAM/SyncRect/", nullptr, false, false, false}},
	{"oWARNING_K3", {"U1/RAM/oWARNING_K3/", nullptr, false, false, false}},
};

bool Warnings::State = true;

void Warnings::init() {
	for (auto& e : Tags) {
		std::string& tag = (std::string&)e.second.Tag;
		e.second.pBit = (TBit*)IniResources::getSignalByTag(tag);
	}
	HandlerSubscribers::set("U1/RAM/", SlotU1RAMUpdate);
}


void Warnings::update(const std::string& PosMem, const TSlotHandlerArsg& args) {
    for (auto& e : Tags) {
        std::string& Tag = (std::string&)e.second.Tag;
        bool isDeviceTag = Tag.find(PosMem) != std::string::npos;

        if (isDeviceTag) {
            TBit* p = e.second.pBit;
            if (p != nullptr) {
                std::string res = p->getValue(args, "");

                if (res == "0" || res == "1") {
                    e.second.isValid = true;

                    // Проверяем: это один из тех двух параметров, где "0" — это авария/предупреждение?
                    if (e.first == "DExS_PWR_LNK" || e.first == "SyncRect") {
                        // Здесь: если пришел "1" -> норма (true), если "0" -> предупреждение (false)
                        e.second.State = (res == "1") ? true : false;
                    }
                    else {
                        // Если пришел "0" -> норма (true), если "1" -> предупреждение (false)
                        e.second.State = (res == "0") ? true : false;
                    }
                }
                else {
                    e.second.isValid = false;
                }
            }
        }
    }
}

bool Warnings::checkState(void) {
	bool hasWarnings = false;
	for (auto& e : Tags) {
		if (e.second.isValid) {
			if (!e.second.State) { 
				hasWarnings = true;
				break; 
			}
		}
	}
	return hasWarnings; 
}

bool Warnings::isTagInWarning(TTrackedBit& element) {
	return (element.isValid && !element.State);
}

void Warnings::SlotU1RAMUpdate(TSlotHandlerArsg args) {
	update("U1/RAM/", args);
	State = checkState();

	LedWarnings::setState(State ? 1 : 0);
}