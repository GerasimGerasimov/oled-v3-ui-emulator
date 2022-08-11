#include "WrappedText.h"

bool TWrappedText::ProcessMessage(TMessage* m) {
    return true;
}

void  TWrappedText::view(void) {//вывести строку на экране
    fillBackGround();
    outText();
}

void TWrappedText::outText() {
    /*
    s16 Left = ElementRect.Left;
    s16 Top = ElementRect.Top;
    if (Style & (int)LabelsStyle::ALIGN_CENTER) {
        Left = (ElementRect.Width - TextSize.width) / 2;
    }
    TGrahics::outText(Caption, Left, Top, ColorScheme.Color, Font);
    */
}

const u16 TWrappedText::getHeight(void) {
    TTextSizes tsizes = getSize();
    return tsizes.height;
}

void TWrappedText::fillBackGround() {
    /*
    if (Style & (int)LabelsStyle::LS_BGRN_TRANSPARENT) return;
    TTextSizes tsizes = getSize();
    TFillRect rect{ ElementRect.Left, ElementRect.Top, tsizes.width, tsizes.height, ColorScheme.BackGround };
    TGrahics::fillRect(rect);
    */
}

void TWrappedText::setText(std::string text) {//добавить/изменить текст в строке
    /*
    if (Caption != caption) {
        Caption = caption;
        if (Style & (int)LabelsStyle::ALIGN_CENTER) {
            TextSize = TMCUFonts::getTextSizes(Caption, Font);
        }
    }
    */
}

TTextSizes TWrappedText::getSize(void) {
    /*
    if (Style == (int)LabelsStyle::LS_DINAMIC) {
        return TMCUFonts::getTextSizes(Caption, Font);
    }
    else {
        return { ElementRect.Width, ElementRect.Height };
    }*/
    return { ElementRect.Width, ElementRect.Height };
}

TWrappedText::TWrappedText(TLabelInitStructure init)
    : TVisualObject({init.focused, init.Rect })
    /*
    , PrimaryColor(init.PrimaryColor)
    , SelectedColor(init.SelectedColor)
    , Style((int)init.style)
    , Font((init.font != "") ? init.font : "Verdana12")
    , Caption(init.caption)
    , TextSize(TMCUFonts::getTextSizes(Caption, Font))
    */ {
}

TWrappedText::~TWrappedText() {//деструктор
}
