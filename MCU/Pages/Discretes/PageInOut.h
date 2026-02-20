#ifndef T_PAGE_INOUT_H
#define T_PAGE_INOUT_H

#include "Pages.h"
#include "TVerticalContainer.h"
#include "HandleSubscribers.h"

class TPageInOut : public TPage
{
public:
    virtual void view();
    virtual const u16 getHeight(void) { return 0; };
    void onOpen();
    void startToClose();
    bool ProcessMessage(TMessage* m);
    TPageInOut(std::string Name);
    ~TPageInOut();
private:
    
    
    
    void SlotUpdate(TSlotHandlerArsg args);
    TVisualObject* getSignalOfFocusedChild();
    int SubscriberID = 0;
protected:
    virtual void fillPageContainer();
    TVerticalContainer* TagList;
    TVerticalContainer* Container;
};

#endif
