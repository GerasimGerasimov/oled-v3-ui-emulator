#include "Label.h"

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

TLabel::TLabel(TLabelInitStructure init)
    : TVisualObject({init.focused, init.Rect })
    , PrimaryColor(init.PrimaryColor)
    , SelectedColor(init.SelectedColor)
    , Style((int)init.style)
    , Caption(init.caption)
    , Font((init.font != "") ? init.font : "Verdana12") {
}

TLabel::~TLabel() {//����������
}
