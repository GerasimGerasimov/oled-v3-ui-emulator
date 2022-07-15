#include "signal.h"
#include <parser.h>

ISignal::ISignal(char* source, int scrLen) 
	: Name (NULL)
	, Comment (NULL)
	, optional (NULL)
	, MSU (NULL) {
	
}

ISignal::ISignal(TSignalPropsPointers props)
	: Name (props.pName)
	, Comment (props.pComment)
    , optional (props.pOptional)
	, MSU (NULL) {
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

std::string ISignal::getMSU()
{
	return (MSU)
		? IniParser::getElement('/', MSU)
		: "";
}
