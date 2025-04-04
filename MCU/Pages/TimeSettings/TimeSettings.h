#pragma once

#include <PageBasicSettings.h>

class TTimeSettings : public TPageBasicSettings
{
public:
    TTimeSettings(std::string Name);
protected:
    void fillPageContainer() override;
};

