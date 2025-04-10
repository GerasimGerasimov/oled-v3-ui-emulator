#pragma once

#include "Pages.h"
#include "TVerticalContainer.h"

class TPageFactorySettings : public TPage
{
private:
    void fillValue();
public:
    TPageFactorySettings(std::string Name);
    ~TPageFactorySettings();
    void onOpen() override;
    void view() override;
    bool ProcessMessage(TMessage* m) override;
    void startToClose() override;
protected:
    TVerticalContainer* Container;
    TVerticalContainer* TagList;
    virtual void fillPageContainer();
};

