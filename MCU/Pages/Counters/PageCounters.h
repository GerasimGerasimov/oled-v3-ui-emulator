#ifndef T_PAGE_COUNTERS_H
#define T_PAGE_COUNTERS_H

#include "Pages.h"
#include "TComponentListVertical.h"
#include "Label.h"

class TPageCounters : public TPage
{
public:
    virtual void view();//������� ������ �� ������
    virtual const u16 getHeight(void) { return 0; };
    void clear();//������� ������
    bool ProcessMessage(TMessage* m);//���������� ���������
    TPageCounters(std::string Name);//�����������
    ~TPageCounters();//����������
    virtual bool onEnter(void);
private:
    TLabel* pLabel1;
    TComponentListVertical* Container;
};

#endif