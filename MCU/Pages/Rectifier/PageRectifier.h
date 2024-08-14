#pragma once

#include "ControlSettings/PageControlSettings.h"

class TPageRectifier : public TPageControlSettings
{
public:
	TPageRectifier(std::string Name);
protected:
	void fillPageContainer(void) override;
};

