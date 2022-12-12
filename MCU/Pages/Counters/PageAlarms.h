#ifndef T_PAGE_ALARMS_H
#define T_PAGE_ALARMS_H

#include "Pages.h"
#include "TComponentListVertical.h"
#include "LinkLabel.h"
#include "Label.h"
#include <HeaderLabel.h>

class TPageAlarms : public TPage
{
public:
    virtual void view();//������� ������ �� ������
    virtual const u16 getHeight(void) { return 0; };
    void clear();//������� ������
    bool ProcessMessage(TMessage* m);//���������� ���������
    TPageAlarms(std::string Name);//�����������
    ~TPageAlarms();//����������
    void onOpen();
private:
    THeaderLabel* pHeader;
    TComponentListVertical* Container;
};

#endif