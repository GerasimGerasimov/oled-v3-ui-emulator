#include "signal.h"
#include <parser.h>

ISignal::ISignal(char* source, int scrLen) 
	: Name (NULL)
	, optional (NULL) {
}

ISignal::ISignal(TSignalPropsPointers props)
	: Name (props.pName)
    , optional (props.pOptional) {
}

ISignal::~ISignal(){
}

std::string ISignal::getName() {
	return (Name)
		? IniParser::getElement('/', Name)
		: "";
}

std::string ISignal::getValue(TSlotHandlerArsg args) {
	return "unknown";
}

std::string ISignal::getDefaultValue() {
	return "**.**";
}

std::string ISignal::getMSU()
{
	return "";
}