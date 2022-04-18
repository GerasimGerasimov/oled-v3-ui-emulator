#include "Label.h"

//����� "������ ������"
void  TLabel::view() {//������� ������ �� ������
    TColorScheme ColorScheme = (inFocus)
        ? SelectedColor
        : PrimaryColor;

    TTextSizes tsizes = getSize();
    TFillRect rect {ElementRect.Left, ElementRect.Top, ElementRect.Width, ElementRect.Height, ColorScheme.BackGround };
    TGrahics::fillRect(rect);
    TGrahics::outText(Caption, ElementRect.Left, ElementRect.Top, ColorScheme.Color, Font);
}

void TLabel::setCaption(std::string caption) {//��������/�������� ����� � ������
    Caption = caption;
}

void TLabel::setFont(std::string font) {//��������/�������� ����� � ������
    Font = font;
}

TTextSizes TLabel::getSize(void) {
    if (Style.bits.Dinamic) {
        return TMCUFonts::getTextSizes(Caption, Font);
    }
    else {
        return { ElementRect.Width, ElementRect.Height };
    }
}

TLabel::TLabel(TLabelInitStructure init) {//�����������
    inFocus = init.focused;
    setFont((init.font != "") ? init.font : "Verdana12");
    PrimaryColor = init.PrimaryColor;
    SelectedColor = init.SelectedColor;
    Style = init.style;
    ElementRect = init.Rect;
    setCaption(init.caption);
}

TLabel::~TLabel() {//����������
}
