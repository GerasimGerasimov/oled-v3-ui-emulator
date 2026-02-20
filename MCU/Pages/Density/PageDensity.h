#pragma once
#include "PageSensors.h"
class TPageDensity : public TPageSensors
{
public: 
	TPageDensity(std::string Name);
protected:
	void fillPageContainer();
};

