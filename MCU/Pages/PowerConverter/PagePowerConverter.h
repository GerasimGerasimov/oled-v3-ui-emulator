#pragma once

#include "ControlSettings/PageControlSettings.h"

class TPagePowerConverter : public TPageControlSettings
{
public:
    TPagePowerConverter(std::string Name);
protected:
    void fillPageContainer() override;
};

