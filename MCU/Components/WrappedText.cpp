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
Надо разбить на строки входяшие в ширину экрана. Каждый символ переноса начинает новую строку.
Начать с разбивки строки на слова разделённые пробелами, потом формировать строки*/

void TWrappedText::setText(std::string text) {//добавить/изменить текст в строке
    //на слова разбил
    std::vector<std::string> words = IniParser::getListOfDelimitedStrInclude(' ', (char*) text.c_str(), text.size());
    //теперь группировать по предложениям вмещающимся в ширину этого элемента
    std::vector<std::string> sentences = {};
    std::string sentence = "";
    u16 maxwidth = ElementRect.Width;
    u16 sw, tsw = 0;
    for (std::string word : words) {
        word += " ";
        TTextSizes ts = TMCUFonts::getTextSizes(word, Font);
        tsw += ts.width;
        if (tsw < maxwidth) {
            sentence += word;
            /*TODO не попадает последнее предложение*/
        }
        else {
            sentences.push_back(sentence);
            sentence = word;
            tsw = ts.width;
        }
    }
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
