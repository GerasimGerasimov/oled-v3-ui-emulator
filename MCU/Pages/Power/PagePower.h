#pragma once

#include <PageSensors.h>

class TPagePower : public TPageSensors
{
public:
    TPagePower(std::string Name);
protected:
    void fillPageContainer(void) override;
};

