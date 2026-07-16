#pragma once
#include <ControlSettings/PageControlSettings.h>
class TpageGeneratorProtection :
    public TPageControlSettings
{
public:
    TpageGeneratorProtection(std::string Name);
protected:
    void fillPageContainer(void) override;
};

