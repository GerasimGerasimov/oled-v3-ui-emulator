#pragma once
#include "Pages.h"
#include "TVerticalContainer.h"
#include "HandleSubscribers.h"

class TPagePowerSettings : public TPage
{
public:
    virtual void view();
    void onOpen();
    void startToClose();
    bool ProcessMessage(TMessage* m);
    TPagePowerSettings(std::string Name);
    ~TPagePowerSettings();
private:
    void SlotUpdate(TSlotHandlerArsg args);
    TVisualObject* getSignalOfFocusedChild();
    int SubscriberID = 0;
protected:
    TVerticalContainer* Container;
    TVerticalContainer* TagList;
    void fillPageContainer();
};

