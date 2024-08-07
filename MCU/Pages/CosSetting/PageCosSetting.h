#pragma once

#include <PageBasicSettings.h>

class TPageCosSetting : public TPageBasicSettings
{
public:
    TPageCosSetting(std::string Name);
protected:
    void fillPageContainer(void) override;
};

