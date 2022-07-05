#include "IniResources.h"
#include "parser.h"

const static std::vector<std::string> SectioNameOrder = { "vars", "RAM", "FLASH", "CD"};

const static std::map<std::string, std::string> SectionNameMap = { {"vars","[vars]"}, {"RAM","[RAM]"}, {"FLASH","[FLASH]"},{"CD","[CD]"} };

std::map<std::string, std::map<std::string, std::map<std::string,ISignal*>>> IniResources::Sources = {};
/*TODO обеспечить такую структуру
U1
 |-vars
 |   |-S1=
 |
 |-RAM
 |   |-p0=
 |
 |-FLASH
 |-CD
*/

void IniResources::init(void) {
	readSources();
}

std::string IniResources::getComment(TValueSearchStruct srch) {
	if (Sources.count(srch.device)) {
		std::map<std::string, std::map<std::string, ISignal*>> devmap = Sources.at(srch.device);
		if (devmap.count(srch.section)) {
			std::map<std::string, ISignal*> signals = devmap.at(srch.section);
			if (signals.count(srch.name)) {
				ISignal* s = signals.at(srch.name);
			}
		}
	}
	/*
	ISignal* s = */
	return std::string();
}

bool IniResources::readSources(void)
{
	TItemLimits itemLimits = TInternalResources::getItemLimitsByName((char*)"SOURCES");
	if (itemLimits.RootOffset) {
		IniParser::setRoot(itemLimits.RootOffset, itemLimits.Size);
		std::vector<std::string> sources = IniParser::getListOfDelimitedSting('/', itemLimits.RootOffset, itemLimits.Size);
		for (auto& src : sources) {
			itemLimits = TInternalResources::getItemLimitsByName((char*)src.c_str());
			if (itemLimits.RootOffset) {
				IniParser::setRoot(itemLimits.RootOffset, itemLimits.Size);
				for (auto& section : SectioNameOrder) {
					std::string value = SectionNameMap.at(section);
					if (IniParser::setSectionToRead((char*)value.c_str())) {
						//std::vector<ISignal*> params = {};
						TSectionReadResult readResult = { NULL, 0 };
						while ((readResult = IniParser::getNextTagString()), readResult.result != 0) {
							 ISignal* s = (section == "vars")
								? TIniString::getScale(section, readResult.tag, readResult.result)
								: TIniString::getSignal(section, readResult.tag, readResult.result);
							 if (s) {
								 std::string name = s->getName();
								 Sources[src][section][name] = s;
							 }
						}
					}
				}
			}
		}
	}
	return false;
}