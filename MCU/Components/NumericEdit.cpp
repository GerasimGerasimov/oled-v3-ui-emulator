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
                    valueUp();
                    break;
                case (u32)KeyCodes::Down:
                    valueDown();
                    break;
                }
            break;
        case (u32)EventSrc::TIMER:
                blinkCursor();
            break;
    }
    return true;
}

template <std::size_t SIZE>
int findIndex(const std::array<char, SIZE>& src, const char trg) {
    int idx = 0;
    for (auto& e : src) {
        if (e == trg) {
            return idx;
        }
        idx++;
    }
    return -1;
}

template <std::size_t SIZE>
char getNextSimbol(const std::array<char, SIZE>& src, const char trg) {
    int idx = findIndex(src, trg);
    if (idx != -1) {
        return src[(idx+1)%src.size()];
    }
    return ' ';
}

template <std::size_t SIZE>
char getPrevSimbol(const std::array<char, SIZE>& src, const char trg) {
    int idx = findIndex(src, trg);
    if (idx != -1) {
        idx = ((idx - 1) >= 0) ? idx - 1 : src.size()-1;
        return src[idx % src.size()];
    }
    return ' ';
}

void TNumericEdit::valueUp(void) {
    if (Position > 0) {
        upFraction();
        return;
    }
    if (Position < 0) {
        upIntegers();
    }
}

void TNumericEdit::valueDown(void) {
    if (Position > 0) {
        downFraction();
        return;
    }
    if (Position < 0) {
        downIntegers();
    }
}

void TNumericEdit::upIntegers(void) {
    int idx = abs(Position) - 1;
    char c = Integers[idx].c;
    c = getNextSimbol(IntPossibleValues, c);
    if (c) {
        Integers[idx].c = c;
    }
}

void TNumericEdit::downIntegers(void) {
    int idx = abs(Position) - 1;
    char c = Integers[idx].c;
    c = getPrevSimbol(IntPossibleValues, c);
    if (c) {
        Integers[idx].c = c;
    }
}

void TNumericEdit::upFraction(void) {
    char c = Fractions[Position - 1].c;
    c = getNextSimbol(FracPossibleValues, c);
    if (c) {
        Fractions[Position - 1].c = c;
    }
}
void TNumericEdit::downFraction(void) {
    char c = Fractions[Position - 1].c;
    c = getPrevSimbol(FracPossibleValues, c);
    if (c) {
        Fractions[Position - 1].c = c;
    }
}

void TNumericEdit::shiftCursorLeft(void) {
    if (Position > -NE_INT_SIZE) {
        Position--;
        if (Position > 0) {
            doFracShiftCursorLeft();
        }
        if (Position < 0) {
            doIntShiftCursorLeft();
        }
    }

}

void TNumericEdit::shiftCursorRight(void) {
    if (Position < NE_FRAC_SIZE) {
        Position++;
        if (Position > 0) {
            doFracShiftCursorRight();
        }
        if (Position < 0) {
            doIntShiftCursorRight();
        }
    }
}

void TNumericEdit::doFracShiftCursorLeft() {
    u16 Count = NE_FRAC_SIZE;
    while (Count--) {
        TCharSignificance& e = Fractions[Count];
        if (e.sig) {
            if (e.c == '0') {
                e.sig = false;
                break;
            }
            else {
                break;
            }
        }
    }
}

void TNumericEdit::doIntShiftCursorLeft() {
    int idx = abs(Position) - 1;
    int pred = ((idx - 1) < 0) ? 0 : (idx - 1);
    char cpred = Integers[pred].c;
    if (!Integers[idx].sig) {
        Integers[idx].sig = true;
        //Если число имеет знак минус, то при перемещении курсора влево минус передвигается влево
        //а его ячейка заменяется НУЛЁМ
        if (cpred == '-') {
            Integers[idx].c = '-';
            Integers[pred].c = '0';
        }
    }
}

void TNumericEdit::doFracShiftCursorRight() {
    int idx = Position - 1;
    if (!Fractions[idx].sig) {
        Fractions[idx].sig = true;
    }
}

void TNumericEdit::doIntShiftCursorRight() {
    /*удаление лишних нулей перед числом*/
    /*TODO и надо удалить двойные минусы, один оставить*/
    u16 Count = NE_INT_SIZE;
    while (Count--) {
        TCharSignificance& e = Integers[Count];
        if (e.sig) {
            if (e.c == '0') {
                e.sig = false;
                break;
            }
            else {
                break;
            }
        }
    }
    /*TODO и надо удалить нули после минуса, кроме последнего нуля (перед запятой)*/
}

void TNumericEdit::blinkCursor(void) {

}

void  TNumericEdit::view(void) {//вывести строку на экране
    TColorScheme ColorScheme = PrimaryColor;
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
    /*тут выделится только запятая*/
    ColorScheme = PrimaryColor;
    CharSize = TMCUFonts::getCharSizes('.', Font);
    TGrahics::fillRect({ cLeft, cTop , CharSize.width, CharSize.height, (u16)((Position == 0) ? 1 : 0) });
    TGrahics::putChar('.', (u16&)cLeft, cTop, (Position == 0)?0:1);

    /*тут выделятся числа после запятой*/
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

void TNumericEdit::setCaption(std::string caption) {
    if (Caption != caption) {
        Caption = caption;
        if (Style & (int)LabelsStyle::TEXT_ALIGN_CENTER) {
            TextSize = TMCUFonts::getTextSizes(Caption, Font);
        }
    }
    /*TODO найти в строке "запятую" и если её нет, то в конец строки додавить запятую */
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
    Integers[4] = { '0', false };
    Integers[5] = { '0', false };
    Integers[6] = { '0', false };
    Integers[7] = { '0', false };
    Integers[8] = { '0', false };

    Fractions[0] = { '0', true };
    Fractions[1] = { '1', true };
    Fractions[2] = { '0', false };
    Fractions[3] = { '0', false };
    Fractions[4] = { '0', false };
}

TNumericEdit::~TNumericEdit() {//деструктор
}
