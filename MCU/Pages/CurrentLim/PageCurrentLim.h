#pragma once

#include "ControlSettings/PageControlSettings.h"

class TPageCurrentLim : public TPageControlSettings
{
public:
    TPageCurrentLim(std::string Name);
protected:
    void fillPageContainer() override;
};

