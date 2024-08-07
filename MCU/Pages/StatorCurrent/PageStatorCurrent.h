#pragma once

#include <PageBasicSettings.h>

class TPageStatorCurrent : public TPageBasicSettings
{
public:
    TPageStatorCurrent(std::string Name);
protected:
    void fillPageContainer(void) override;
};

