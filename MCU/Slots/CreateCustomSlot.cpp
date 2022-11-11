#include "CreateCustomSlot.h"
#include "CommonSlotHandler.h"

Slot* CreateCustomSlot::init(std::string devname, std::string section) {
	/*
	std::vector <Slot> res;
	for (auto& device : Devices) {
		std::string devname = device.first;
		TDeviceNetworkProps slotsprops = device.second;
		for (auto& slotprop : slotsprops.SlotsMap) {
			std::string section = slotprop.first;
			TDeviceSlotProps* prop = slotprop.second;
			Slot* pSlot = new Slot(devname, section, prop->StartAddr, prop->LastAddr);
			pSlot->addcmd(getReadCmdFromSettings(slotsprops.NetworkAddr, prop->StartAddr, prop->LastAddr));
			pSlot->onData = CommonSlotHandler::parseRespond;
			res.push_back(*pSlot);
		}
	}
	*/
	Slot* res = new Slot(devname, section, 0, 0);
	return res;
}

