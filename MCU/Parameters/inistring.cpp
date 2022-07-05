#include "inistring.h"
#include "vars.h"
#include "parameters.h"
#include "signalfactory.h"

pSignal TIniString::getSignal(std::string section, char* source, int scrLen) {
	TSignalPropsPointers props = SignalFactoty::getSignalProps(source, scrLen);
	pSignal s = SignalFactoty::getSignal(props);
	return s;
}

pSignal TIniString::getScale(std::string section, char* source, int scrLen) {
	TSignalPropsPointers props = SignalFactoty::getScaleProps(source, scrLen);
	pSignal s = SignalFactoty::getScale(props);
	return s;
}

