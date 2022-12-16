#ifndef VERTICAL_CONTAINER_H
#define VERTICAL_CONTAINER_H

#include "TComponentsContainer.h"
#include "stm32f4xx.h"
#include "msg.h"
#include "graphics.h"

class TVerticalContainer : public TComponentsContainer
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
    TVerticalContainer(std::vector <TVisualObject*> Source = {});//�����������
    ~TVerticalContainer();//����������
    virtual bool onEnter(void);
  private:
    u16 GetViewObjectsCount();//���-�� �������� ����������� � ������ ���� �� FirstPosition �� ������� ����
    void goUp(void);
    void goDown(void);
    void drawScrollBar(void);
};

#endif