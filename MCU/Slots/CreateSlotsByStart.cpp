#include "CreateSlotsByStart.h"

void CreateSlotsByStart::init(std::map<std::string, TDeviceNetworkProps> Devices) {
	for (auto& device : Devices) {
		std::string devname = device.first;
		TDeviceNetworkProps slotsprops = device.second;
		for (auto& slotprop : slotsprops.SlotsMap) {
			std::string section = slotprop.first;
			TDeviceSlotProps* prop = slotprop.second;
			/*TODO собственно создать слот для заданного COM порта*/
		}
	}
}

