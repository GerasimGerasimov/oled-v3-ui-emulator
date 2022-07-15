#ifndef T_PAGE_HOME_H
#define T_PAGE_HOME_H

#include "Pages.h"
#include "TComponentListVertical.h"
#include "TagLine.h"

class TPageHome : public TPage
{
public:
    virtual void view();//вывести объект на экране
    virtual const u16 getHeight(void) { return 0; };
    void clear();//очистит список
    bool ProcessMessage(TMessage* m);//обработчик сообщений
    TPageHome(std::string Name);//конструктор
    ~TPageHome();//деструктор
private:
    TComponentListVertical* MainMenu;
    TTagLine* pLTagUref;
    TTagLine* pLTagIref;
    TTagLine* pLTagUoutAve;
    TTagLine* pLTagIoutAve;
    TTagLine* pLTagSparkFrq;
    //TLinkedTagLabel* pLTagOut;
    //TLinkedTagLabel* pLTagIinAve;
    void goToTagInfoPage(int a);
};

#endif