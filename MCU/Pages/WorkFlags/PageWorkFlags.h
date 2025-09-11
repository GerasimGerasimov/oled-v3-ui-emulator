#pragma once
#include <PageSensors.h>
class TPageWorkFlags : public TPageSensors
{
public:
    TPageWorkFlags(std::string Name);
protected:
    void fillPageContainer() override;
};


