#pragma once
#include "PageSensors.h"
class TPageDebugInfo : public TPageSensors
{
public:
	TPageDebugInfo(std::string Name);
protected: 
	void fillPageContainer();
};

