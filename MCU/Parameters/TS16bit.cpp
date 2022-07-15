#include "TS16BIT.h"

TS16BIT::TS16BIT(char* source, int scrLen) : TParameter(source, scrLen) {
}

TS16BIT::TS16BIT(TSignalPropsPointers props) : TParameter(props) {
	
}

TS16BIT::~TS16BIT(){
}
