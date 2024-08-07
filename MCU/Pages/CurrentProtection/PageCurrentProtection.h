#pragma once

#include <PageBasicSettings.h>

class TPageCurrentProtection : public TPageBasicSettings
{
public:
    TPageCurrentProtection(std::string Name);
protected:
    void fillPageContainer(void) override;
};

