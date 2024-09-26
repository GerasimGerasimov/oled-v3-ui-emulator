#pragma once

#include <PageBasicSettings.h>

class TPageDelayProtection : public TPageBasicSettings
{
public:
    TPageDelayProtection(std::string Name);
protected:
    void fillPageContainer(void) override;
};

