#ifndef LABEL_H
#define LABEL_H

#include <string>
#include "common.h"
#include "graphics.h"

struct TColorScheme {
    u16 Color;
    u16 BackGround;
};

typedef union {
    u16	   i;
    struct {//����� ������
        unsigned Dinamic : 1;
        unsigned Fixed : 1;
    } bits;
} LabelStyle;//����� ���������� � ���������;

struct TLabelInitStructure {
    bool focused = false;
    std::string caption = "";
    std::string font = "Verdana12";
    LabelStyle style = { 0 };
    TColorScheme PrimaryColor = { PRIMARY_COLOR , BACKGROUND_COLOR }; //�������� �������� ����� 
    TColorScheme SelectedColor = { BACKGROUND_COLOR, PRIMARY_COLOR };//�������� ����� ��� ���������
    TElementRect Rect = { 0, 0, 64, 10 };
};

//������ ������
class TLabel : public TVisualObject {
public:
    void view();//������� ������ �� ������
    void setCaption(std::string caption);//�������� ����� � ������ ������� � �����
    void setFont(std::string font);//�������� ����� � ������ ������� � �����
    TTextSizes getSize(void);
    TLabel(TLabelInitStructure init);//�����������
    ~TLabel();//����������
private:
    std::string Font;
    std::string Caption;
    TColorScheme PrimaryColor; //�������� �������� ����� 
    TColorScheme SelectedColor;//�������� ����� ��� ���������
    LabelStyle Style;
};

#endif