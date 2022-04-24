#ifndef T_PAGE_H
#define T_PAGE_H

#include "TComponentsContainer.h"
#include "stm32f4xx.h"
#include "msg.h"

class TPage : public TComponentsContainer
{
public:
    bool isOpen;
    //� ����� �� ����� ������ ���� ��������, ���� ���-�� ����� �� ���������� �� �������
    TVisualObject* pFocusedElement;//������ ����������� � ������
    virtual void view();//������� ������ �� ������
    virtual const u16 getHeight(void) { return 0; };
    void clear();//������� ������
    void ProcessMessage(TMessage* m);//���������� ���������
    TPage(bool isOpenState, std::vector <TVisualObject*> Source = {});//�����������
    ~TPage();//����������
};

#endif