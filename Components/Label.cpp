#include "Label.h"

#include "graphics.h"

//����� "������ ������"
void  TLabel::View() {//������� ������ �� ������
  /*TTextProperty TextProperty = {
    //������� �������������� ���� ��������� ������� �����
    Left,//u16 MinLeft;
    Top,//u16 MinTop;
    Left+Width,//u16 MaxRight;
    Top+Height,//u16 MaxBottom;
    //��������� ���������� ������ (������������ �������������� ���� ��������� ������� �����)
    //�.�. ��� ����� ���� � ��������������
    0,//s16 X;
    0,//s16 Y;
    //������������ ������
    //0 - ������� ����� � ����� ������� ��������������� ��������������
    //1 - ������� ����� � ������ ������� ��������������� ��������������
    //2 - ���������� ����� ����� � ������ ��������� ��������������� ��������������
    0,//u8 Align;
    //���� ������
    TextColor,//u8 Color;
    //����� ���������� �������/������
    font,//FONT_INFO* font;
  };*/
    u8 i = 0;
    u8 j = 0;
    u8 c;

    u16 fone_color = NEG_COLOR;
    u16 text_color = BASIC_COLOR;

    if (Focus) {
        fone_color = BASIC_COLOR;
        text_color = NEG_COLOR;
    }

    //TextProperty.Color = text_color;
    TFillRect rect{ Left, Top, MAX_RIGHT, Height, fone_color };
    TGrahics::fillRect(rect);
    TTextProps textProps{ Left, Top, text_color, fone_color };
    TGrahics::outText(textProps, Caption);
}

u16 GetStrWidth(std::string s, const FONT_INFO* font) {//���������� ������ ������
    u16 w = 0;
    char* pC = (char*)s.c_str();
    while (*pC++ != 0) {
        w += font->charInfo[*pC - 0x21].widthBits;
    }
    return w;
}

#define max_str_size 0x100 //������ ����, ����� ����������� �� ����� ������

u16 GetStrLength(char* s) {//���������� ����� ������
    u16 l = 0;
    while (*s++ != 0) {
        l++;
        //���� ������ ������ 255 ��������, �� ���������� � � 255
        //�������������� 255-� ���� ��� "0"
        if (l == max_str_size) break;
    }
    return l;
}

void TLabel::SetCaption(std::string NewCaption) {//��������/�������� ����� � ������
    Caption = NewCaption;
}

TLabel::TLabel(std::string caption) {//�����������
    Focus = false;
    //������������� ����������� ������
    SetCaption((caption != "") ? caption : "default");
    //����a �� ���������
    TextColor = BASIC_COLOR;
    FoneColor = NEG_COLOR;
    //������� ������
    Left = 80;  //
    Top = 0;   //
    //���� �� ���������
    font = &FontInfomSReferenceSansSerif6pt;
    Height = font->CharHeight;//������ ������ = ������ ������� � ������ ������
    Width = GetStrWidth(Caption, font); //������ ������ = ����� ����� �������� � ������
    //
}

TLabel::~TLabel() {//����������
}
