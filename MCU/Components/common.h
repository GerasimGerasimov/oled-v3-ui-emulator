#ifndef COMMON_VISUAL_H
#define COMMON_VISUAL_H

#include <stm32f4xx.h>

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
    virtual void View();//������� ������ �� ������
    TVisualObject();//�����������
    ~TVisualObject();//����������
};

#endif