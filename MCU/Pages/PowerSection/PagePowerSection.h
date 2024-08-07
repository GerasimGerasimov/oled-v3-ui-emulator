#pragma once

#include <PageBasicSettings.h>

class TPagePowerSection : public TPageBasicSettings
{
public:
    TPagePowerSection(std::string Name);
protected:
    void fillPageContainer(void) override;
};

