//#ifndef T_PAGE_CONTROL_SETTINGS_H
//#define T_PAGE_CONTROL_SETTINGS_H

#include "Pages.h"
#include "TVerticalContainer.h"
#include "HandleSubscribers.h"

class TPageControlSettings : public TPage
{
public:
    virtual void view();
    virtual const u16 getHeight(void) { return 0; };
    void onOpen();
    void startToClose();
    bool ProcessMessage(TMessage* m);
    TPageControlSettings(std::string Name);
    ~TPageControlSettings();
private:
    TVerticalContainer* Container;
    TVerticalContainer* TagList;
    void fillPageContainer(void);
    void SlotUpdate(TSlotHandlerArsg args);
    TVisualObject* getSignalOfFocusedChild();
    int SubscriberID = 0;
};

//#endif
