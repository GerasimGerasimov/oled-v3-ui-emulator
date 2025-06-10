#pragma once
#include "Pages.h"
#include "TVerticalContainer.h"
#include "HandleSubscribers.h"

class TPageLimiters : public TPage
{
public:
    virtual void view();
    void onOpen();
    void startToClose();
    bool ProcessMessage(TMessage* m);
    TPageLimiters(std::string Name);
    ~TPageLimiters();
private:
    void SlotUpdate(TSlotHandlerArsg args);
    TVisualObject* getSignalOfFocusedChild();
    int SubscriberID = 0;
protected:
    TVerticalContainer* Container;
    TVerticalContainer* TagList;
    void fillPageContainer();
};

