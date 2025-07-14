#pragma once
#include <PageBasicSettings.h>
class TPageShakerSettings : public TPageBasicSettings
{
public:
    TPageShakerSettings(std::string Name);
protected:
    void fillPageContainer() override;
};

