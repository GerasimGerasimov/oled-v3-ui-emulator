#pragma once

#include <PageBasicSettings.h>

class TPageRegulatorSettings : public TPageBasicSettings
{
public:
	TPageRegulatorSettings(std::string Name);
protected:
	virtual void fillPageContainer(void) override;
};

