#pragma once
#include <Pages.h>
#include "TVerticalContainer.h"
#include "HandleSubscribers.h"

class TPageAutoMode :
    public TPage
{
public:
    virtual void view();
    virtual const u16 getHeight(void) { return 0; };
    void onOpen();
    void startToClose();
    bool ProcessMessage(TMessage* m);
    TPageAutoMode(std::string Name);
    ~TPageAutoMode();
private:
    void SlotUpdateFLASH(TSlotHandlerArsg args);
    void SlotUpdateRAM(TSlotHandlerArsg args);
    void SlotUpdateCD(TSlotHandlerArsg args);
    void SlotUpdate(const char* sector, TSlotHandlerArsg args);
    TVisualObject* getSignalOfFocusedChild();
    int SubscriberIDFLASH = 0;
    int SubscriberIDRAM = 0;
    int SubscriberIDCD = 0;
protected:
    TVerticalContainer* Container;
    TVerticalContainer* TagList;
    virtual void fillPageContainer(void);
};

