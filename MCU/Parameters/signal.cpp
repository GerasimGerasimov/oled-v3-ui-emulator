#include "signal.h"
#include <parser.h>

ISignal::ISignal(char* source, int scrLen) {
	Name = 	Comment = optional = NULL;
}

ISignal::ISignal(TSignalPropsPointers props) {
	Name = props.pName;
	Comment = props.pComment;
	optional = props.pOptional;
}

ISignal::~ISignal(){
}

std::string ISignal::getName() {
	return (Name)
		? IniParser::getElement('/', Name)
		: "";
}

std::string ISignal::getComment() {
	return (Comment)
		? IniParser::getElement('/', Comment)
		: "";
}
