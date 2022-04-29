#ifndef T_PAGE_MAIN_MENU_H
#define T_PAGE_MAIN_MENU_H

#include "Pages.h"
#include "TComponentListVertical.h"
#include "LinkLabel.h"
#include "Label.h"

class TPageMainMenu : public TPage
{
public:
    virtual void view();//������� ������ �� ������
    virtual const u16 getHeight(void) { return 0; };
    void clear();//������� ������
    bool ProcessMessage(TMessage* m);//���������� ���������
    TPageMainMenu(std::string Name);//�����������
    ~TPageMainMenu();//����������
    virtual bool onEnter(void);
private:
    TComponentListVertical* MainMenu;
    TLabelInitStructure LabelInit;
    TLinkLabel* pLabel1;
    TLabel* pLabel2;
    TLabel* pLabel3;
    TLabel* pLabel4;
    TLabel* pLabel5;
    TLabel* pLabel6;
    TLabel* pLabel7;
    TLabel* pLabel8;
    TLabel* pLabel9;
};

#endif