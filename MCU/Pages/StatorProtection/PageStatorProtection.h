#pragma once

#include <PageBasicSettings.h>

class TPageStatorProtection : public TPageBasicSettings
{
public:
    TPageStatorProtection(std::string Name);
protected:
    void fillPageContainer(void) override;
};

