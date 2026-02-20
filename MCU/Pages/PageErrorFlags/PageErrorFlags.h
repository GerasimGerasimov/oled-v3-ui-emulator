#pragma once
#include "PageSensors.h"
class TPageErrorFlags : public TPageSensors
{
public:
	TPageErrorFlags(std::string Name);
protected:
	void fillPageContainer() override;
};

