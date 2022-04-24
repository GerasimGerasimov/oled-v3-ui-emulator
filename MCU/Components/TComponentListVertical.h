#ifndef MENU_H
#define MENU_H

#include <string>
#include <vector>
#include "common.h"
#include "stm32f4xx.h"
#include "msg.h"
#include "graphics.h"

class TComponentListVertical : public TVisualObject 
{
  public:
    bool isOpen;
    //� ����� �� ����� ������ ���� ��������, ���� ���-�� ����� �� ���������� �� �������
    u16 FocusLine;//������ ����������� � ������
    u16 FirstPosition;//������ ������������ ������ ������� �������� � ��
    u16 LastPosition; //��������� ������������ ������
    virtual void view(void);//������� ������ �� ������
    virtual u16 getHeight(void);
    void Add(TVisualObject* pVisualObject);//�������� ������ � ������
    void AddList(std::vector <TVisualObject*> Source);//�������� ������ �������� � ������
    void Clear();//������� ������
    void ProcessMessage(TMessage* m);//���������� ���������
    TComponentListVertical(std::vector <TVisualObject*> Source = {});//�����������
    ~TComponentListVertical();//����������
    const u16 ItemsCount() const;
  private:
    std::vector <TVisualObject*> List;
    u16 GetViewObjectsCount();//���-�� �������� ����������� � ������ ���� �� FirstPosition �� ������� ����
    //u16 Items;//���������� �������� � ������
};

#endif