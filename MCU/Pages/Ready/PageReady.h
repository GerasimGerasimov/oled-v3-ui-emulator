#pragma once

#include "ControlSettings/PageControlSettings.h"

class TPageReady : public TPageControlSettings
{
public:
	TPageReady(std::string Name);
protected:
	virtual void fillPageContainer(void) override;
};

