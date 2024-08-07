#pragma once

#include <PageBasicSettings.h>

class TPageAutoMode : public TPageBasicSettings
{
public:
    TPageAutoMode(std::string Name);
protected:
    void fillPageContainer(void) override;
};

