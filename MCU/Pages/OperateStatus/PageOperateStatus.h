#ifndef T_PAGE_OPERATE_STATUS_H
#define T_PAGE_OPERATE_STATUS_H

#include "Pages.h"
#include "TVerticalContainer.h"
#include "HandleSubscribers.h"

class TPageOperateStatus : public TPage
{
public:
    virtual void view();//вывести объект на экране
    virtual const u16 getHeight(void) { return 0; };
    void onOpen();
    bool ProcessMessage(TMessage* m);//обработчик сообщений
    void startToClose();
    TPageOperateStatus(std::string Name);//конструктор
    ~TPageOperateStatus();//деструктор
private:
    TVerticalContainer* Container;
    void SlotU1RAMUpdate(TSlotHandlerArsg args);
    TVisualObject* getSignalOfFocusedChild();
    int SubscriberID;
};

#endif