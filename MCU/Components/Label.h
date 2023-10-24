#ifndef LABEL_H
#define LABEL_H

#include <string>
#include "common.h"
#include "graphics.h"

struct TColorScheme {
    u16 Color;
    u16 BackGround;
};

enum class LabelsStyle : u32 {
    WIDTH_DINAMIC = 1,
    WIDTH_FIXED   = 2,
    BGRND_TRANSPARENT = 4,
    TEXT_ALIGN_CENTER = 8,
    HOLD_SELECTED_STYLE = 16,
    FIXED_HEADER = 32,
    FIXED_FOOTER = 64,
    CLIPPED = 128
};

struct TLabelInitStructure {
    bool focused = false;
    std::string caption = "";
    std::string font = "Verdana12";
    LabelsStyle style = LabelsStyle::WIDTH_DINAMIC;
    TColorScheme PrimaryColor = { PRIMARY_COLOR , BACKGROUND_COLOR }; //�������� �������� ����� 
    TColorScheme SelectedColor = { BACKGROUND_COLOR, PRIMARY_COLOR };//�������� ����� ��� ���������
    TElementRect Rect = { 0, 0, 64, 10 };
    TVisualObject* pOwner = nullptr;
};

//������ ������
class TLabel : public TVisualObject {
public:
    virtual void view(void);//������� ������ �� ������
    virtual const u16 getHeight(void);
    void setCaption(std::string caption);//�������� ����� � ������ ������� � �����
    std::string getCaption(void);
    void setFont(std::string font);//�������� ����� � ������ ������� � �����
    TTextSizes getSize(void);
    TLabel(TLabelInitStructure init);//�����������
    ~TLabel();//����������
protected:
    std::string Font;
    std::string Caption;
    TTextSizes TextSize;
    TColorScheme PrimaryColor; //�������� �������� ����� 
    TColorScheme SelectedColor;//�������� ����� ��� ���������
    int Style;
    void fillBackGround(TColorScheme& ColorScheme);
    void outCaption(TColorScheme& ColorScheme);
};

#endif