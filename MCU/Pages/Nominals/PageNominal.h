#pragma once

#include <PageBasicSettings.h>

class TPageNominal : public TPageBasicSettings
{
public:
	TPageNominal(std::string Name);
protected:
	virtual void fillPageContainer(void) override;
};

