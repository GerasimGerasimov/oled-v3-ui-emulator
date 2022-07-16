#include "TU8BIT.h"

TU8BIT::TU8BIT(TSignalPropsPointers props)
	: TGeneralCaseSignal(props)
	, Addr({0,0}) {
	
}

TU8BIT::~TU8BIT(){
}

std::string TU8BIT::getValue()
{
	return "TU8";
}
