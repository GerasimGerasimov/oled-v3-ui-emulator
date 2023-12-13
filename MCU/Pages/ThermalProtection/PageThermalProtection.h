#pragma once

#include <PageBasicSettings.h>

class TPageThermalProtection : public TPageBasicSettings
{
public:
	TPageThermalProtection(std::string Name);
protected:
	virtual void fillPageContainer(void) override;

};

