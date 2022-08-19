#include "NumericEdit.h"


bool TNumericEdit::ProcessMessage(TMessage* m) { 
    switch (m->Event) {
        case (u32)EventSrc::KEYBOARD:
            switch (m->p1) {
                case (u32)KeyCodes::Left:
                    shiftCursorLeft();
                    break;
                case (u32)KeyCodes::Right:
                    shiftCursorRight();
                    break;
                case (u32)KeyCodes::Up:
                    break;
                case (u32)KeyCodes::Down:
                    break;
                }
            break;
        case (u32)EventSrc::TIMER:
                blinkCursor();
            break;
    }
    return true;
}

void TNumericEdit::shiftCursorLeft(void) {
    Position--;
}
void TNumericEdit::shiftCursorRight(void) {
    Position++;
}

void TNumericEdit::blinkCursor(void) {

}

//����� "������ ������"
void  TNumericEdit::view(void) {//������� ������ �� ������
    TColorScheme ColorScheme = PrimaryColor;
    //fillBackGround(ColorScheme);
    outCaption(ColorScheme);
}

void TNumericEdit::outCaption(TColorScheme& ColorScheme) {
    s16 Left = ElementRect.Left;
    s16 Top = ElementRect.Top;
    /*
    if (Style & (int)LabelsStyle::TEXT_ALIGN_CENTER) {
        Left = (ElementRect.Width - TextSize.width) / 2;
    }
    */
    TTextSizes CharSize;
    s16 cTop = Top;
    s16 cLeft = Left;

    u16 height = TMCUText::setFont(Font);
    u16 Count = Integers.size();
    ColorScheme = PrimaryColor;
    while (Count--) {
        TCharSignificance e = Integers[Count];
        if (e.sig) {
            /*TODO �� ���������� ������ ����� ����� �������*/
            if (Position < 0) {
                s16 pos = -(Count+1);
                ColorScheme = (pos == Position)
                    ? SelectedColor
                    : PrimaryColor;
            }
            CharSize = TMCUFonts::getCharSizes(e.c, Font);
            TGrahics::fillRect({ cLeft, cTop , CharSize.width, CharSize.height, ColorScheme.BackGround });
            TGrahics::putChar(e.c, (u16&) cLeft, cTop, ColorScheme.Color);
        }
    }
    /*TODO ��� ������ ��������� ������ �������*/
    ColorScheme = PrimaryColor;
    CharSize = TMCUFonts::getCharSizes('.', Font);
    TGrahics::fillRect({ cLeft, cTop , CharSize.width, CharSize.height, (u16)((Position == 0) ? 1 : 0) });
    TGrahics::putChar('.', (u16&)cLeft, cTop, (Position == 0)?0:1);

    /*TODO ��� ������� ��������� ����� ����� �������*/
    Count = 0;
    for (auto& e : Fractions) {
        Count++;
        if (e.sig) {
            if (Position > 0) {
                s16 pos = (Count);
                ColorScheme = (pos == Position)
                    ? SelectedColor
                    : PrimaryColor;
            }
            CharSize = TMCUFonts::getCharSizes(e.c, Font);
            TGrahics::fillRect({ cLeft, cTop , CharSize.width, CharSize.height, ColorScheme.BackGround });
            TGrahics::putChar(e.c, (u16&)cLeft, cTop, ColorScheme.Color);
        }
    }
}

const u16 TNumericEdit::getHeight(void) {
    TTextSizes tsizes = getSize();
    return tsizes.height;
}

void TNumericEdit::fillBackGround(TColorScheme& ColorScheme) {
    TTextSizes tsizes = getSize();
    TFillRect rect{ ElementRect.Left, ElementRect.Top, tsizes.width, tsizes.height, ColorScheme.BackGround };
    TGrahics::fillRect(rect);
}

void TNumericEdit::setCaption(std::string caption) {//��������/�������� ����� � ������
    if (Caption != caption) {
        Caption = caption;
        if (Style & (int)LabelsStyle::TEXT_ALIGN_CENTER) {
            TextSize = TMCUFonts::getTextSizes(Caption, Font);
        }
    }
    /*TODO ����� � ������ "�������" � ���� � ���, �� � ����� ������ �������� ������� */
}

TTextSizes TNumericEdit::getSize(void) {
   return { ElementRect.Width, ElementRect.Height };
}

TNumericEdit::TNumericEdit(TLabelInitStructure init)
    : TVisualObject({init.focused, init.Rect })
    , PrimaryColor(init.PrimaryColor)
    , SelectedColor(init.SelectedColor)
    , Style((int)init.style)
    , Font((init.font != "") ? init.font : "Verdana12")
    , Caption(init.caption)
    , TextSize(TMCUFonts::getTextSizes(Caption, Font))
    , Position(0)
    {
    Integers[0] = { '3', true };
    Integers[1] = { '2', true };
    Integers[2] = { '1', true };
    Integers[3] = { '-', true };

    Fractions[0] = { '0', true };
    Fractions[1] = { '1', true };
}

TNumericEdit::~TNumericEdit() {//����������
}
