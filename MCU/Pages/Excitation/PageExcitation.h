#pragma once

#include <PageBasicSettings.h>

class TPageExcitation : public TPageBasicSettings
{
public:
	TPageExcitation(std::string Name);
protected:
	void fillPageContainer(void) override;
};

