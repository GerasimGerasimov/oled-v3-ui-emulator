#pragma once

#include <PageSensors.h>

class TPageExcitation : public TPageSensors
{
public:
	TPageExcitation(std::string Name);
protected:
	virtual void fillPageContainer(void) override;
};

