#pragma once

#include <PageBasicSettings.h>

class TPageGeneratorMode : public TPageBasicSettings
{
public:
    TPageGeneratorMode(std::string Name);
protected:
    void fillPageContainer(void) override;
};

