#ifndef T_PAGE_ALARMS_H
#define T_PAGE_ALARMS_H

#include "Pages.h"
#include "TComponentListVertical.h"
#include "LinkLabel.h"
#include "Label.h"

class TPageAlarms : public TPage
{
public:
    virtual void view();//вывести объект на экране
    virtual const u16 getHeight(void) { return 0; };
    void clear();//очистит список
    bool ProcessMessage(TMessage* m);//обработчик сообщений
    TPageAlarms(std::string Name);//конструктор
    ~TPageAlarms();//деструктор
private:
    TLabel* pLabel1;
    TLabel* pLabel2;
    TLinkLabel* pLabel3;
    TComponentListVertical* Container;
};

#endif