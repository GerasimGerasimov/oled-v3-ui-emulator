#pragma once

#include <PageSensors.h>

class TPageReady : public TPageSensors
{
public:
    TPageReady(std::string Name);
protected:
    void fillPageContainer() override;
};

