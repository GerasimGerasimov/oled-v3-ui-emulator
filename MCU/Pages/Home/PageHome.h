#ifndef T_PAGE_HOME_H
#define T_PAGE_HOME_H

#include "Pages.h"
#include "TVerticalContainer.h"
#include "HandleSubscribers.h"
#include <Indicator.h>
#include <GroupIndicators.h>

class TPageHome : public TPage
{
public:
    virtual void view();
    virtual const u16 getHeight(void) { return 0; };
    void onOpen();
    void startToClose();
    bool ProcessMessage(TMessage* m);
    TPageHome(std::string Name);
    ~TPageHome();
    void SlotUpdateRAM(TSlotHandlerArsg args);
private:
    TVerticalContainer* TagList;
    void fillPageContainer(void);
    void SlotUpdate(const char* sector, TSlotHandlerArsg args);
    void SlotUpdateFLASH(TSlotHandlerArsg args);
    TVisualObject* getSignalOfFocusedChild();
    int SubscriberID = 0;
    int SubIDFlash = 0;
    Indicator IndicatorU;
    Indicator IndicatorI;
    GroupIndicators groupIndicators;
    std::vector <TVisualObject*> container;
    unsigned int component = 0;
    
};

#endif