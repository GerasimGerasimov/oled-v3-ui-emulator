#pragma once

#include <PageSensors.h>

class TPageCurrentLimit : public TPageSensors
{
public:
    TPageCurrentLimit(std::string Name);
protected:
    void fillPageContainer(void) override;
};

