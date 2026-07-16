#pragma once
#include "ControlSettings/PageControlSettings.h"
class TPageAsynchronousProtection :
    public TPageControlSettings
{
public:
    TPageAsynchronousProtection(std::string Name);
protected:
    void fillPageContainer(void) override;
    
};

