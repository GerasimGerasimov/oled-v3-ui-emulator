#include "vars.h"
#include <parser.h>

TScale::TScale(char* source, int scrLen) : ISignal(source, scrLen) {
}

TScale::TScale(TSignalPropsPointers props) : ISignal(props) {
}

TScale::~TScale(){
}

std::string TScale::getName() {
	std::string s = (Name)
		? IniParser::getElement('=', Name)
		: "";
	return s;
}