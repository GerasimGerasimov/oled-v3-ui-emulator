#ifndef VERTICAL_CONTAINER_H
#define VERTICAL_CONTAINER_H

#include "TComponentsContainer.h"
#include "stm32f4xx.h"
#include "msg.h"
#include "graphics.h"

typedef struct TVerticalContainerProps {
    bool EnableScrollBar;
};

class TVerticalContainer : public TComponentsContainer
{
  public:
    bool isOpen;
    bool EnableScrollBar;
    //� ����� �� ����� ������ ���� ��������, ���� ���-�� ����� �� ���������� �� �������
    u16 FocusedLine;//������ ����������� � ������
    u16 FirstPosition;//������ ������������ ������ ������� �������� � ��
    u16 LastPosition; //��������� ������������ ������
    virtual void view(void);//������� ������ �� ������
    virtual const u16 getHeight(void);
    virtual void  Clear(void);//������� ������
    bool ProcessMessage(TMessage* m);//���������� ���������
    virtual TVisualObject* getFocusedElement();//��� �����������
    TVerticalContainer(TVerticalContainerProps& props, std::vector <TVisualObject*> Source = {});//�����������
    ~TVerticalContainer();//����������
    virtual bool onEnter(void);
  private:
    u16 GetViewObjectsCount();//���-�� �������� ����������� � ������ ���� �� FirstPosition �� ������� ����
    u16 getScrollBarWidth();
    void goUp(void);
    void goDown(void);
    void drawScrollBar(void);
};

#endif