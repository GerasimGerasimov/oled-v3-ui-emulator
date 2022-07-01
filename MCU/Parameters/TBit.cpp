#include "TBit.h"

TBit::TBit(char* source, int scrLen) : ISignal(source, scrLen) {
}

TBit::TBit(TSignalPropsPointers props) : ISignal(props) {
	
}

TBit::~TBit(){
}
