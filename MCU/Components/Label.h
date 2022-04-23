#ifndef LABEL_H
#define LABEL_H

#include <string>
#include "common.h"
#include "graphics.h"

struct TColorScheme {
    u16 Color;
    u16 BackGround;
};

enum class LabelsStyle {
    LS_DINAMIC = 1,
    LS_FIXED   = 2
};


struct TLabelInitStructure {
    bool focused = false;
    std::string caption = "";
    std::string font = "Verdana12";
    LabelsStyle style = LabelsStyle::LS_FIXED;
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
    LabelsStyle Style;
};

#endif