#pragma once

#include "ControlSettings/PageControlSettings.h"

class TPageVoltageLim : public TPageControlSettings
{
public:
    TPageVoltageLim(std::string Name);
protected:
    void fillPageContainer() override;
};

