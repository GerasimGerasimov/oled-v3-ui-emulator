#pragma once
#include <PageBasicSettings.h>
class TPageCommunicationSettings : public TPageBasicSettings
{
public:
    TPageCommunicationSettings(std::string Name);
protected:
    void fillPageContainer() override;
};


