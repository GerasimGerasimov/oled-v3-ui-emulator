#ifndef INI_RESOURCES_H
#define INI_RESOURCES_H

#include "resources.h"
#include <vector>
#include <map>
#include "inistring.h"
#include "signal.h"

typedef struct {
	std::string device;
	std::string section;
	std::string name;
} TValueSearchStruct;

class IniResources {
public:
	static void init(void);
	static ISignal* getSignalByTag(std::string tag);
	static std::string getComment(TValueSearchStruct srch);
private:
	static std::map<std::string, std::map<std::string, std::map<std::string, ISignal*>>> Sources;
	static bool readSources(void);
	static TValueSearchStruct TagToValueSearchStruct(std::string tag);
};

#endif