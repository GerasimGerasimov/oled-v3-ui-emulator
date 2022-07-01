#include "TS16BIT.h"

TS16BIT::TS16BIT(char* source, int scrLen) : ISignal(source, scrLen) {
}

TS16BIT::TS16BIT(TSignalPropsPointers props) : ISignal(props) {
	
}

TS16BIT::~TS16BIT(){
}
