#pragma once

#include <PageSensors.h>

class TPageInformationSignals : public TPageSensors
{
public:
	TPageInformationSignals(std::string Name);
protected:
	virtual void fillPageContainer(void) override;
};

