#include "TFloat.h"
#include "ParametersUtils.h"

TFloat::TFloat(TSignalPropsPointers props)
	: TGeneralCaseSignal(props)
	, Addr(ParametersUtils::getByteOffsetFromSlahedAddrStr(strAddr)) {
	
}

TFloat::~TFloat(){
}
