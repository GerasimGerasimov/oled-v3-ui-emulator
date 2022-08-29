#ifndef COMMON_VISUAL_H
#define COMMON_VISUAL_H

#include <stm32f4xx.h>
#include "msg.h"
#include <vector>

struct TElementRect {
    s16 Left;  //
    s16 Top;   //
    u16 Height;//
    u16 Width; //
};

struct TVisualObjectInitStructure {
    bool focused = false;
    TElementRect Rect = { 0, 0, 64, 10 };
};

class TVisualObject {//������� ����� ���������� ��������
public:
    //���������� ����������� ������� � ������
    bool inFocus = false;//false-�� � ������ true-� ������
    //������� ������ (������ �������� � �������� ������)
    TElementRect ElementRect;
    virtual void view(void) = 0;//������� ������ �� ������
    virtual bool ProcessMessage(TMessage* m) { return false; };
    virtual const u16 getHeight(void) = 0;//������� ������ �� ������
    virtual TVisualObject* getFocusedElement();//��� �����������
    TVisualObject();
    TVisualObject(TVisualObjectInitStructure props);
    virtual ~TVisualObject();
    void* getDataSrc();
protected:
    void* DataSrc;
};

#endif