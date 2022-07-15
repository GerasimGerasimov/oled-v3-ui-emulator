#include "parameters.h"
#include <parser.h>

TParameter::TParameter(char* source, int scrLen) 
	: ISignal(source, scrLen)
	, Comment(NULL)
	, MSU(NULL) {
}

TParameter::TParameter(TSignalPropsPointers props)
	: ISignal(props)
	, Comment(props.pComment)
	, MSU(NULL) {
}

TParameter::~TParameter(){
}
/// <summary>
/// 
/// </summary>
/// <returns></returns>
std::string TParameter::getComment() {
	return (Comment)
		? IniParser::getElement('/', Comment)
		: "";
}

std::string TParameter::getMSU()
{
	std::string name = getName();
	return (MSU)
		? IniParser::getElement('/', MSU)
		: "";
}