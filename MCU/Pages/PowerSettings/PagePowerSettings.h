#pragma once
#include "PageBasicSettings.h"
#include "TVerticalContainer.h"
#include "HandleSubscribers.h"

class TPagePowerSettings : public TPageBasicSettings
{
public:
    TPagePowerSettings(std::string Name);
protected:
    void fillPageContainer() override;
};

