#include "parameters.h"
#include <parser.h>

TParameter::TParameter(char* source, int scrLen) 
	: ISignal(source, scrLen)
	, Comment(NULL)
	, MSU(NULL) {
}

TParameter::TParameter(TSignalPropsPointers props)
	: ISignal(props)
	, Comment(props.pComment)
	, MSU(NULL) {
}

TParameter::~TParameter(){
}
/// <summary>
/// 
/// </summary>
/// <returns></returns>
std::string TParameter::getComment() {
	return (Comment)
		? IniParser::getElement('/', Comment)
		: "";
}

/*
Где находится MSU
p17802=P/C/TPrmList/xF09E/r204F.L///x00#DI/x01#AIN_DI/x02#EXTAIN_DI/const/

p13321=P/C/TBit    /xF042/mask/r2021.1/1/1/const/

//общий случай для MSU.. но TODO сначала надо распарсить option 
p65301=P/C/TByte   /xE06A/rC035.L/msu/scale/bytes//const/
p17100=P/C/TInteger/xF090/r2048  /msu/scale/bytes//const/
p60200=P/C/TWORD   /xE004/rC002  /msu/scale/bytes//const/
p60000=P/C/TDWORD  /xE000/rC000  /msu/scale/bytes//const/
p62800=P/C/TFloat  /xE038/rC01C  /msu/scale/bytes//const/

*/
std::string TParameter::getMSU()
{
	return (MSU)
		? IniParser::getElement('/', MSU)
		: "";
}