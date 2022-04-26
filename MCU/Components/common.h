#ifndef COMMON_VISUAL_H
#define COMMON_VISUAL_H

#include <stm32f4xx.h>
#include "msg.h"

struct TElementRect {
    s16 Left;  //
    s16 Top;   //
    u16 Height;//
    u16 Width; //
};

class TVisualObject {//������� ����� ���������� ��������
public:
    //���������� ����������� ������� � ������
    bool inFocus = false;//false-�� � ������ true-� ������
    //������� ������ (������ �������� � �������� ������)
    TElementRect ElementRect;
    virtual void view(void) = 0;//������� ������ �� ������
    virtual void ProcessMessage(TMessage* m) {};
    virtual const u16 getHeight(void) = 0;//������� ������ �� ������
    virtual ~TVisualObject();//����������
};

#endif