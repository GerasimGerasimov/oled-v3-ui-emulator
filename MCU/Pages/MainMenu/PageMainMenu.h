#ifndef T_PAGE_MAIN_MENU_H
#define T_PAGE_MAIN_MENU_H

#include "Pages.h"
#include "TComponentListVertical.h"
#include "Label.h"

class TPageMainMenu : public TPage
{
public:
    virtual void view();//������� ������ �� ������
    virtual const u16 getHeight(void) { return 0; };
    void clear();//������� ������
    void ProcessMessage(TMessage* m);//���������� ���������
    TPageMainMenu();//�����������
    ~TPageMainMenu();//����������
private:
    TComponentListVertical* MainMenu;
    TLabelInitStructure LabelInit;
    TLabel* pLabel1;
    TLabel* pLabel2;
    TLabel* pLabel3;
    TLabel* pLabel4;
    TLabel* pLabel5;
};

#endif