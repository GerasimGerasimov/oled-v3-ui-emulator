#ifndef T_PAGE_BASIC_SETTINGS_H
#define T_PAGE_BASIC_SETTINGS_H

#include "Pages.h"
#include "TVerticalContainer.h"
#include "HandleSubscribers.h"

class TPageBasicSettings : public TPage
{
public:
    virtual void view();
    virtual const u16 getHeight() { return 0; };
    void onOpen();
    void startToClose();
    bool ProcessMessage(TMessage* m);
    TPageBasicSettings(std::string Name);
    ~TPageBasicSettings();
private:
    void SlotUpdate(TSlotHandlerArsg args);
    TVisualObject* getSignalOfFocusedChild();
    int SubscriberID = 0;
protected:
    TVerticalContainer* Container;
    TVerticalContainer* TagList;
    virtual void fillPageContainer();
};

#endif