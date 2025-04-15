#pragma once

#include <PageBasicSettings.h>

class TPageRegulatorKoeff : public TPageBasicSettings
{
public:
    TPageRegulatorKoeff(std::string Name);
protected:
    void fillPageContainer() override;
};

