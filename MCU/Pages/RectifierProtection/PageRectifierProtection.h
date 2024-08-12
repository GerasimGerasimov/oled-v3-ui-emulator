#pragma once

#include <PageBasicSettings.h>

class TPageRectifierProtection : public TPageBasicSettings
{
public:
    TPageRectifierProtection(std::string Name);
protected:
    void fillPageContainer(void) override;
};

