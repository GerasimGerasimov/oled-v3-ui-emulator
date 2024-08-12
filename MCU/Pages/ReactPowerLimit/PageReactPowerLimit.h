#pragma once

#include <PageBasicSettings.h>

class TPageReactPowerLimit : public TPageBasicSettings
{
public:
    TPageReactPowerLimit(std::string Name);
protected:
    void fillPageContainer(void) override;
};

