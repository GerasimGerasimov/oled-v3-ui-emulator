#pragma once

#include <PageSensors.h>

class TPageTesting : public TPageSensors
{
public:
    TPageTesting(std::string Name);
protected:
    void fillPageContainer(void) override;
};

