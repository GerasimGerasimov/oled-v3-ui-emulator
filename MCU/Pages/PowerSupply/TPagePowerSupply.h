#pragma once
#include "ControlSettings/PageControlSettings.h"

class TPagePowerSupply :
    public TPageControlSettings
{
public:
    TPagePowerSupply(std::string Name);
protected:
    virtual void fillPageContainer() override;
};

