#pragma once
#include "PageSensors.h"

class TPagePowerSupply : public TPageSensors
{
public:
    TPagePowerSupply(std::string Name);
protected:
    virtual void fillPageContainer() override;
};

