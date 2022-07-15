#include "TFloat.h"

TFloat::TFloat(char* source, int scrLen) : TParameter(source, scrLen) {
}

TFloat::TFloat(TSignalPropsPointers props) : TParameter(props) {
	
}

TFloat::~TFloat(){
}
