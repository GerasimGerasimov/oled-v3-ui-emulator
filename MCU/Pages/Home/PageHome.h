#ifndef T_PAGE_HOME_H
#define T_PAGE_HOME_H

#include "Pages.h"
#include "TComponentListVertical.h"
#include "TagLine.h"

class TPageHome : public TPage
{
public:
    virtual void view();//������� ������ �� ������
    virtual const u16 getHeight(void) { return 0; };
    void clear();//������� ������
    bool ProcessMessage(TMessage* m);//���������� ���������
    TPageHome(std::string Name);//�����������
    ~TPageHome();//����������
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