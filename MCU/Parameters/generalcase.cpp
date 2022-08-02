#include "generalcase.h"
#include <parser.h>

TGeneralCaseSignal::TGeneralCaseSignal(TSignalPropsPointers props)
	: TParameter(props)
	, MSU(IniParser::getElementPtrByNumber(2, '/', props.pOptional)) {
	strAddr = IniParser::getElementPtrByNumber(1, '/', props.pOptional);
}

TGeneralCaseSignal::~TGeneralCaseSignal(){
}

/*
Где находится MSU

//Special case One
p19802=P/C/TPrmList/xF0C9/r2064.H/msu//x03#9600/x04#19200/x05#57600/x06#115200/const/

//Special case Two
p13321=P/C/TBit    /xF042/mask/r2021.1/1/1/const/ вообще нет MSU

//General case
//общий случай для MSU.. но TODO сначала надо распарсить option там содержится msu 
                   |options
				   |0     1       2
p65301=P/C/TByte   /xE06A/rC035.L/msu/scale/bytes//const/
p17100=P/C/TInteger/xF090/r2048  /msu/scale/bytes//const/
p60200=P/C/TWORD   /xE004/rC002  /msu/scale/bytes//const/
p60000=P/C/TDWORD  /xE000/rC000  /msu/scale/bytes//const/
p62800=P/C/TFloat  /xE038/rC01C  /msu/scale/bytes//const/
*/

std::string TGeneralCaseSignal::getMSU()
{
	return (MSU)
		? IniParser::getElement('/', MSU)
		: "";
}

void TGeneralCaseSignal::setValue() {}

std::string TGeneralCaseSignal::getValue(const TSlotHandlerArsg& args, const char* format) {
	return "TGeneralCaseSignal";
}
