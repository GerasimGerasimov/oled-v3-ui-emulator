#pragma once

#include <PageSensors.h>

class TPageConverter : public TPageSensors
{
public:
    TPageConverter(std::string Name);
protected:
    void fillPageContainer() override;
};

