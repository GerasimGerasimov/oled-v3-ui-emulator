#pragma once
#include "Pages.h"
#include "TVerticalContainer.h"
#include "HandleSubscribers.h"

class TPageRegulatorSettings :
    public TPage
{
public:
    virtual void view();
    void onOpen();
    void startToClose();
    bool ProcessMessage(TMessage* m);
    TPageRegulatorSettings(std::string Name);
    ~TPageRegulatorSettings();
private:
    void SlotUpdate(TSlotHandlerArsg args);
    TVisualObject* getSignalOfFocusedChild();
    int SubscriberID = 0;
protected:
    TVerticalContainer* Container;
    TVerticalContainer* TagList;
    void fillPageContainer();
};

