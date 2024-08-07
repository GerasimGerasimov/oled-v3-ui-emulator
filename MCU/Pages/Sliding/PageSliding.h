#pragma once

#include <PageSensors.h>

class TPageSliding : public TPageSensors
{
public:
    TPageSliding(std::string Name);
protected:
    void fillPageContainer(void) override;
};

