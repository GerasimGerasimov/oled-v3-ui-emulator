#ifndef INI_RESOURCES_H
#define INI_RESOURCES_H

#include "resources.h"
#include <vector>
#include <map>
#include "inistring.h"
#include "signal.h"

typedef struct {
	u16 Interval;
	u16 StartAddr;
	u16 LastAddr;
} TDeviceSlotProps;

typedef struct {
	std::string Source;
	std::string COM;
	u16 NetworkAddr;
	std::map<std::string, TDeviceSlotProps*> SlotsMap; //Key is RAM, FLASH, CD
} TDeviceNetworkProps;

class IniResources {
public:
	static void init(void);
	static std::map<std::string, std::map<std::string, std::vector<ISignal*>>> Sources;
	static std::map<std::string, TDeviceNetworkProps> Devices;
private:
	static bool readSources(void);
	static bool readDevices(void);
	static TDeviceNetworkProps getDeviceNetworkProps(char* src, int size);
};

#endif