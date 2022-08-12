#include "WrappedText.h"
#include "parser.h"

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

/*TODO сюда попадает строка, в которой в т.ч. могут быть и символ переноса строки.
Ќадо разбить на строки вход€шие в ширину экрана.  аждый символ переноса начинает новую строку.
Ќачать с разбивки строки на слова разделЄнные пробелами, потом формировать строки
≈сли слово длинное, то его надо тоже разбивать на части, не соблюда€ правила переноса*/

void TWrappedText::setText(std::string text) {//добавить/изменить текст в строке
    //теперь группировать по предложени€м вмещающимс€ в ширину этого элемента
    std::vector<std::string> sentences = {};
    u16 maxwidth = ElementRect.Width;
    std::string s = "";
    for (const char c: text) {
        if (c == '\n') {
            sentences.push_back(s);
            sentences.push_back("");
            s = "";
            continue;
        }
        TTextSizes ts = TMCUFonts::getTextSizes(s+c, Font);
        if (ts.width > maxwidth) {
            sentences.push_back(s);
            s = "";
        }
        s += c;
    }
    if (s != "") {
        sentences.push_back(s);
    }

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
    , Font((init.font != "") ? init.font : "Verdana12")
    /*
    , PrimaryColor(init.PrimaryColor)
    , SelectedColor(init.SelectedColor)
    , Style((int)init.style)
    , Caption(init.caption)
    , TextSize(TMCUFonts::getTextSizes(Caption, Font))
    */ {
}

TWrappedText::~TWrappedText() {//деструктор
}
