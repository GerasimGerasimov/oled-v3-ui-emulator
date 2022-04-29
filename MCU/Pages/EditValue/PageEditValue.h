#ifndef T_PAGE_EDIT_VALUE_H
#define T_PAGE_EDIT_VALUE_H

#include "Pages.h"
#include "TComponentListVertical.h"
#include "LinkLabel.h"
#include "Label.h"

class TPageEditValue : public TPage
{
public:
    virtual void view();//вывести объект на экране
    virtual const u16 getHeight(void) { return 0; };
    void clear();//очистит список
    bool ProcessMessage(TMessage* m);//обработчик сообщений
    TPageEditValue(std::string Name);//конструктор
    ~TPageEditValue();//деструктор
    virtual bool onEnter(void);
private:
    TLabel* pLabel1;
    TLabel* pLabel2;
    TLinkLabel* pLabel3;
    TComponentListVertical* Container;
};

#endif