#pragma once
#include <PageBasicSettings.h>
class TPageUPP :
    public TPageBasicSettings
{
public:
    TPageUPP(std::string Name);
protected:
    void fillPageContainer(void) override;
};

