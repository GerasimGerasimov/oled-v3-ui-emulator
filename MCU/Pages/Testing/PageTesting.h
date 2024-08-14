#pragma once

#include "ControlSettings/PageControlSettings.h"

class TPageTesting : public TPageControlSettings
{
public:
    TPageTesting(std::string Name);
protected:
    void fillPageContainer(void) override;
};

