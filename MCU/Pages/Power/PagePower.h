#pragma once

#include <PageSensors.h>
#include "TVerticalContainer.h"
#include "HandleSubscribers.h"

class TPagePower : public TPage
{
public:
    virtual void view();
    virtual const u16 getHeight(void) { return 0; };
    void onOpen();
    void startToClose();
    bool ProcessMessage(TMessage* m);
    TPagePower(std::string Name);
    ~TPagePower();
private:
    void SlotUpdate(TSlotHandlerArsg args);
    TVisualObject* getSignalOfFocusedChild();
    int SubscriberID = 0;
protected:
    TVerticalContainer* Container;
    TVerticalContainer* TagList;
    virtual void fillPageContainer(void);
};

