#include "TagLineTime.h"



TTagLineTime::TTagLineTime(std::string caption, std::string tag, TLabelInitStructure init) 
	: TTagLine(caption, tag, init){
	delete Value;
	Value = new TLabelTime(init);
}
