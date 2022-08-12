#include "WrappedText.h"
#include "parser.h"

bool TWrappedText::ProcessMessage(TMessage* m) {
    return true;
}

void  TWrappedText::view(void) {//������� ������ �� ������
    fillBackGround();
    outText();
}

void TWrappedText::outText() {
    s16 Left = ElementRect.Left;
    s16 Top = ElementRect.Top;
    for (auto const text : List) {
        TGrahics::outText(text, Left, Top, 1, Font);
        Top+= TMCUFonts::getFontHeight(Font);
    }
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

/*TODO ���� �������� ������, � ������� � �.�. ����� ���� � ������ �������� ������.
���� ������� �� ������ �������� � ������ ������. ������ ������ �������� �������� ����� ������.
������ � �������� ������ �� ����� ���������� ���������, ����� ����������� ������
���� ����� �������, �� ��� ���� ���� ��������� �� �����, �� �������� ������� ��������*/

void TWrappedText::setText(std::string text) {//��������/�������� ����� � ������
    //������ ������������ �� ������������ ����������� � ������ ����� ��������
    std::vector<std::string> res = {};
    u16 maxwidth = ElementRect.Width;
    std::string s = "";
    for (const char c: text) {
        if (c == '\n') {
            res.push_back(s);
            res.push_back("");
            s = "";
            continue;
        }
        TTextSizes ts = TMCUFonts::getTextSizes(s+c, Font);
        if (ts.width > maxwidth) {
            res.push_back(s);
            s = "";
        }
        s += c;
    }
    if (s != "") {
        res.push_back(s);
    }
    List.clear();
    List = res;
}

TTextSizes TWrappedText::getSize(void) {
    u16 h = List.size() * TMCUFonts::getFontHeight(Font);
    return { ElementRect.Width, h };
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

TWrappedText::~TWrappedText() {//����������
}
