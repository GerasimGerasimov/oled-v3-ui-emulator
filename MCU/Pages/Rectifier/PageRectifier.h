#pragma once

#include <PageBasicSettings.h>

class TPageRectifier : public TPageBasicSettings
{
public:
	TPageRectifier(std::string Name);
protected:
	void fillPageContainer(void) override;
};

