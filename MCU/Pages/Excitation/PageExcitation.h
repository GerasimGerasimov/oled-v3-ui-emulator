#pragma once

#include <PageBasicSettings.h>

class TPageExcitation : public TPageBasicSettings
{
public:
	TPageExcitation(std::string Name);
protected:
	virtual void fillPageContainer(void) override;
};

