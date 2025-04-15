#pragma once

#include "ControlSettings/PageControlSettings.h"

class TPageControlVoltageStator : public TPageControlSettings
{
public:
    TPageControlVoltageStator(std::string Name);
protected:
    void fillPageContainer() override;
};

