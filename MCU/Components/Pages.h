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
    TVisualObject* pFocusedElement;//������� ����������� � ������
    virtual void view();//������� ������ �� ������
    virtual const u16 getHeight(void) { return 0; };
    void clear();//������� ������
    bool ProcessMessage(TMessage* m);//���������� ���������
    TPage(std::string name);//�����������
    TPage(std::string name, bool isOpenState, std::vector <TVisualObject*> Source = {});//�����������
    ~TPage();//����������
private:
    std::string Name;
    std::string BackPage;
};

#endif