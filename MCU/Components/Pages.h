#ifndef PAGES_H
#define PAGES_H

#include <vector>
#include "common.h"
#include "stm32f4xx.h"
#include "msg.h"

class TPage : public TVisualObject
{
public:
    bool isOpen;
    //� ����� �� ����� ������ ���� ��������, ���� ���-�� ����� �� ���������� �� �������
    TVisualObject* pFocusedElement;//������ ����������� � ������
    void View();//������� ������ �� ������
    void Add(TVisualObject* pVisualObject);//�������� ������ � ������
    void AddList(std::vector <TVisualObject*> Source);//�������� ������ �������� � ������
    void Clear();//������� ������
    void ProcessMessage(TMessage* m);//���������� ���������
    TPage(bool isOpenState, std::vector <TVisualObject*> Source = {});//�����������
    ~TPage();//����������
private:
    std::vector <TVisualObject*> List;
    u16 GetViewObjectsCount();//���-�� �������� ����������� � ������ ���� �� FirstPosition �� ������� ����
};

#endif