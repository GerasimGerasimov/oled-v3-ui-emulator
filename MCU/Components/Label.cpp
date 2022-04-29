#include "Label.h"

bool TLabel::onEnter(void) {
    return false;
}

//����� "������ ������"
void  TLabel::view(void) {//������� ������ �� ������
    TColorScheme ColorScheme = (inFocus)
        ? SelectedColor
        : PrimaryColor;

    fillBackGround(ColorScheme);
    TGrahics::outText(Caption, ElementRect.Left, ElementRect.Top, ColorScheme.Color, Font);
}

const u16 TLabel::getHeight(void) {
    TTextSizes tsizes = getSize();
    return tsizes.height;
}

void TLabel::fillBackGround(TColorScheme ColorScheme) {
    if (Style & (int)LabelsStyle::LS_BGRN_TRANSPARENT) return;
    TTextSizes tsizes = getSize();
    TFillRect rect{ ElementRect.Left, ElementRect.Top, tsizes.width, tsizes.height, ColorScheme.BackGround };
    TGrahics::fillRect(rect);
}

void TLabel::setCaption(std::string caption) {//��������/�������� ����� � ������
    Caption = caption;
}

void TLabel::setFont(std::string font) {//��������/�������� ����� � ������
    Font = font;
}

TTextSizes TLabel::getSize(void) {
    if (Style == (int)LabelsStyle::LS_DINAMIC) {
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
    Style = (int)init.style;
    ElementRect = init.Rect;
    setCaption(init.caption);
}

TLabel::~TLabel() {//����������
}
