#ifndef MENU_H
#define MENU_H

#include "TComponentsContainer.h"
#include "stm32f4xx.h"
#include "msg.h"
#include "graphics.h"

class TComponentListVertical : public TComponentsContainer
{
  public:
    bool isOpen;
    //� ����� �� ����� ������ ���� ��������, ���� ���-�� ����� �� ���������� �� �������
    u16 FocusedLine;//������ ����������� � ������
    u16 FirstPosition;//������ ������������ ������ ������� �������� � ��
    u16 LastPosition; //��������� ������������ ������
    virtual void view(void);//������� ������ �� ������
    virtual const u16 getHeight(void);
    virtual void  Clear(void);//������� ������
    bool ProcessMessage(TMessage* m);//���������� ���������
    virtual TVisualObject* getFocusedElement();//��� �����������
    TComponentListVertical(std::vector <TVisualObject*> Source = {});//�����������
    ~TComponentListVertical();//����������
  private:
    u16 GetViewObjectsCount();//���-�� �������� ����������� � ������ ���� �� FirstPosition �� ������� ����
    void goUp(void);
    void goDown(void);
};

#endif