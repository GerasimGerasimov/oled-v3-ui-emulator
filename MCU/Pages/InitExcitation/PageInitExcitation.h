#pragma once

#include "PageBasicSettings.h"

class TPageInitExcitation : public TPageBasicSettings
{
public:
    TPageInitExcitation(std::string Name);
protected:
    void fillPageContainer() override;
};

