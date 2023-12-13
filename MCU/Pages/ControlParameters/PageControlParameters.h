#pragma once

#include <PageSensors.h>

class TPageControlParameters : public TPageSensors
{
public:
	TPageControlParameters(std::string Name);
protected:
	virtual void fillPageContainer(void) override;
};

