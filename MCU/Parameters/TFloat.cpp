#include "TFloat.h"

TFloat::TFloat(char* source, int scrLen) : ISignal(source, scrLen) {
}

TFloat::TFloat(TSignalPropsPointers props) : ISignal(props) {
	
}

TFloat::~TFloat(){
}
