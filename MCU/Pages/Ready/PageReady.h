#pragma once

#include <PageSensors.h>

class TPageReady : public TPageSensors
{
public:
	TPageReady(std::string Name);
protected:
	virtual void fillPageContainer(void) override;
};

