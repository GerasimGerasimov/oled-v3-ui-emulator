#include "Label.h"

//класс "строка текста"
void  TLabel::view() {//вывести строку на экране
    TColorScheme ColorScheme = (inFocus)
        ? SelectedColor
        : PrimaryColor;

    TTextSizes tsizes = getSize();
    TFillRect rect {ElementRect.Left, ElementRect.Top, ElementRect.Width, ElementRect.Height, ColorScheme.BackGround };
    TGrahics::fillRect(rect);
    TGrahics::outText(Caption, ElementRect.Left, ElementRect.Top, ColorScheme.Color, Font);
}

void TLabel::setCaption(std::string caption) {//добавить/изменить текст в строке
    Caption = caption;
}

void TLabel::setFont(std::string font) {//добавить/изменить текст в строке
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

TLabel::TLabel(TLabelInitStructure init) {//конструктор
    inFocus = init.focused;
    setFont((init.font != "") ? init.font : "Verdana12");
    PrimaryColor = init.PrimaryColor;
    SelectedColor = init.SelectedColor;
    Style = init.style;
    ElementRect = init.Rect;
    setCaption(init.caption);
}

TLabel::~TLabel() {//деструктор
}
