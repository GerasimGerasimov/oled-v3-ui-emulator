#pragma once

#include <ControlSettings/PageControlSettings.h>

class TPageStatorVoltage : public TPageControlSettings
{
public:
    TPageStatorVoltage(std::string Name);
protected:
    void fillPageContainer(void) override;
};

