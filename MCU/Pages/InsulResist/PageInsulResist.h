#pragma once

#include "ControlSettings/PageControlSettings.h"

class TPageInsulResist : public TPageControlSettings
{
public:
    TPageInsulResist(std::string Name);
protected:
    void fillPageContainer() override;
};

