#include "TBit.h"

TBit::TBit(char* source, int scrLen) : TParameter(source, scrLen) {
}

TBit::TBit(TSignalPropsPointers props) : TParameter(props) {
	
}

TBit::~TBit(){
}
