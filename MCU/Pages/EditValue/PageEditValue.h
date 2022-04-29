#ifndef T_PAGE_EDIT_VALUE_H
#define T_PAGE_EDIT_VALUE_H

#include "Pages.h"
#include "TComponentListVertical.h"
#include "LinkLabel.h"
#include "Label.h"

class TPageEditValue : public TPage
{
public:
    virtual void view();//������� ������ �� ������
    virtual const u16 getHeight(void) { return 0; };
    void clear();//������� ������
    bool ProcessMessage(TMessage* m);//���������� ���������
    TPageEditValue(std::string Name);//�����������
    ~TPageEditValue();//����������
    virtual bool onEnter(void);
private:
    TLabel* pLabel1;
    TLabel* pLabel2;
    TLinkLabel* pLabel3;
    TComponentListVertical* Container;
};

#endif