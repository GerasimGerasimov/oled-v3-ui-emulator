#ifndef LABEL_H
#define LABEL_H

#include <string>
#include "common.h"
#include "fonts.h"

//������ ������
class TLabel : public TVisualObject
{
public:
    const FONT_INFO* font;
    u16 TextColor;//���� ������ (0-������, 1-�����)
    u16 FoneColor;//���� ���� (0-������, 1-�����) (�����������)
    void View();//������� ������ �� ������
    void SetCaption(std::string NewCaption);//�������� ����� � ������ ������� � �����
    TLabel(std::string caption = "");//�����������
    ~TLabel();//����������
private:
    std::string Caption;//������ ��������� �������������� ������ ���������� ������    
};

#endif