#ifndef T_PAGE_ALARMS_H
#define T_PAGE_ALARMS_H

#include "Pages.h"
#include "TVerticalContainer.h"


class TPageAlarms : public TPage
{
public:
    virtual void view();//вывести объект на экране
    virtual const u16 getHeight(void) { return 0; };
    void clear();//очистит список
    bool ProcessMessage(TMessage* m);//обработчик сообщений
    TPageAlarms(std::string Name);//конструктор
    ~TPageAlarms();//деструктор
    void onOpen();
    void startToClose();
private:
    TVerticalContainer* Container;
    TVerticalContainer* AlarmsList;
    void fillPageContainer(void);
    u16 EmptyViewDelay;
};

#endif