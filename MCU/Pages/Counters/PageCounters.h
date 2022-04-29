#ifndef T_PAGE_COUNTERS_H
#define T_PAGE_COUNTERS_H

#include "Pages.h"
#include "TComponentListVertical.h"
#include "Label.h"

class TPageCounters : public TPage
{
public:
    virtual void view();//вывести объект на экране
    virtual const u16 getHeight(void) { return 0; };
    void clear();//очистит список
    bool ProcessMessage(TMessage* m);//обработчик сообщений
    TPageCounters(std::string Name);//конструктор
    ~TPageCounters();//деструктор
    virtual bool onEnter(void);
private:
    TLabel* pLabel1;
    TComponentListVertical* Container;
};

#endif