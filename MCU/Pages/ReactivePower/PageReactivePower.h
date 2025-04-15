#pragma once

#include <PageSensors.h>

class TPageReactivePower : public TPageSensors
{
public:
    TPageReactivePower(std::string Name);
protected:
    void fillPageContainer() override;
};

