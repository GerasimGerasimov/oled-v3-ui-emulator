#pragma once

#include "ControlSettings/PageControlSettings.h"

class TPagePowerLim : public TPageControlSettings
{
public:
    TPagePowerLim(std::string Name);
protected:
    void fillPageContainer() override;
};

