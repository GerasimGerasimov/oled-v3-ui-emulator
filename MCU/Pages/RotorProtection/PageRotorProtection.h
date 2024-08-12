#pragma once

#include <PageBasicSettings.h>

class TPageRotorProtection : public TPageBasicSettings
{
public:
    TPageRotorProtection(std::string Name);
protected:
    void fillPageContainer(void) override;
};

