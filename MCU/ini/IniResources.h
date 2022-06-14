#ifndef INI_RESOURCES_H
#define INI_RESOURCES_H

#include "resources.h"
#include <vector>
#include <map>
#include "inistring.h"
#include "signal.h"

class IniResources {
public:
	static void init(void);
	static std::map<std::string, std::map<std::string, std::vector<ISignal*>>> Sources;
private:
	static bool readSources(void);
};

#endif