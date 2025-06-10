#pragma once
#include "PageBasicSettings.h"
#include "TVerticalContainer.h"
#include "HandleSubscribers.h"


class TPageLimiters : public TPageBasicSettings
{
public:
    TPageLimiters(std::string Name);
protected:
    void fillPageContainer() override;
};

