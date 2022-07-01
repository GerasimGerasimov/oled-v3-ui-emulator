#include "TU16BIT.h"

TU16BIT::TU16BIT(char* source, int scrLen) : ISignal(source, scrLen) {
}

TU16BIT::TU16BIT(TSignalPropsPointers props) : ISignal(props) {
	
}

TU16BIT::~TU16BIT(){
}
