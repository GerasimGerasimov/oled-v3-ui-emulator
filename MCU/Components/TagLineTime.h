#pragma once

#include "TagLine.h"
#include "LabelTime.h"

//класс содержит параметр для отображения в формате ЧЧ:ММ
class TTagLineTime : public TTagLine
{
public:
	
	TTagLineTime(std::string caption, std::string tag, TLabelInitStructure init);
};

