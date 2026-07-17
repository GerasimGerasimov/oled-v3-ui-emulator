#pragma once

#include <ControlSettings/PageControlSettings.h>

class TPageRectifierProtection : public TPageControlSettings
{
public:
    TPageRectifierProtection(std::string Name);
protected:
    void fillPageContainer(void) override;
};

