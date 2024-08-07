#pragma once

#include <PageBasicSettings.h>

class TPageFieldBreak : public TPageBasicSettings
{
public:
    TPageFieldBreak(std::string Name);
protected:
    void fillPageContainer(void) override;
};

