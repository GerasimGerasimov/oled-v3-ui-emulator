#include "TU16BIT.h"
#include "parser.h"
#include "ParametersUtils.h"

TU16BIT::TU16BIT(TSignalPropsPointers props)
	: TGeneralCaseSignal(props)
	, Addr(ParametersUtils::getByteOffsetFromSlahedAddrStr(strAddr)) {
	
}

TU16BIT::~TU16BIT(){
}

std::string TU16BIT::getValue()
{
	if (Addr < 0)
		return "err.addr";
	if (valid) {

	}
	else {
		return "*****";
	}
}
