#ifndef T_PAGE_ALARMS_H
#define T_PAGE_ALARMS_H

#include "Pages.h"
#include "TComponentListVertical.h"
#include "LinkLabel.h"
#include "Label.h"

class TPageAlarms : public TPage
{
public:
    virtual void view();//������� ������ �� ������
    virtual const u16 getHeight(void) { return 0; };
    void clear();//������� ������
    bool ProcessMessage(TMessage* m);//���������� ���������
    TPageAlarms(std::string Name);//�����������
    ~TPageAlarms();//����������
private:
    TLabel* pLabel1;
    TLabel* pLabel2;
    TLinkLabel* pLabel3;
    TComponentListVertical* Container;
};

#endif