#pragma once
#include "PageBasicSettings.h"
class TPageConnectionSetting :
    public TPageBasicSettings
{
public:
    TPageConnectionSetting(std::string Name);
protected:
    void fillPageContainer();
};

