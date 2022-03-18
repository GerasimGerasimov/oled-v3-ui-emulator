#ifndef COMMON_VISUAL_H
#define COMMON_VISUAL_H

#include <stm32f4xx.h>

class TVisualObject {//������� ����� ���������� ��������
public:
    //���������� ����������� ������� � ������
    bool Focus = false;//false-�� � ������ true-� ������
    //������� ������ (������ �������� � �������� ������)
    s16 Left;  //
    s16 Top;   //
    u16 Height;//
    u16 Width; //
    virtual void View();//������� ������ �� ������
    TVisualObject();//�����������
    ~TVisualObject();//����������
};

#endif