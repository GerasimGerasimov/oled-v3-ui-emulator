#pragma once
#include "PageBasicSettings.h"
#include "TVerticalContainer.h"
#include "HandleSubscribers.h"

class TPageRegulatorSettings :
    public TPageBasicSettings
{
public:
    TPageRegulatorSettings(std::string Name);
protected:
    void fillPageContainer() override;
};

