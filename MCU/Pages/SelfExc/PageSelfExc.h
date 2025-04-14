#pragma once

#include <PageBasicSettings.h>

class TPageSelfExc : public TPageBasicSettings
{
public:
    TPageSelfExc(std::string Name);
protected:
    void fillPageContainer(void) override;
};

