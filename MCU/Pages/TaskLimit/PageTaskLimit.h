#pragma once

#include <PageBasicSettings.h>

class TPageTaskLimit : public TPageBasicSettings
{
public:
    TPageTaskLimit(std::string Name);
protected:
    void fillPageContainer(void) override;
};

