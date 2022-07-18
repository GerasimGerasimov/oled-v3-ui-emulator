#include "TS16BIT.h"
#include "ParametersUtils.h"

TS16BIT::TS16BIT(TSignalPropsPointers props)
	: TGeneralCaseSignal (props)
	, Addr(ParametersUtils::getByteOffsetFromSlahedAddrStr(strAddr)) {
	
}

TS16BIT::~TS16BIT(){
}
