#include "NumericEdit.h"


bool TNumericEdit::ProcessMessage(TMessage* m) { 
    switch (m->Event) {
        case (u32)EventSrc::KEYBOARD:
            if (inFocus) {
                switch (m->p1) {
                case (u32)KeyCodes::Left:
                    shiftCursorLeft();
                    m->Event = (u32) EventSrc::NONE;
                    return true;
                case (u32)KeyCodes::Right:
                    shiftCursorRight();
                    m->Event = (u32)EventSrc::NONE;
                    return true;
                case (u32)KeyCodes::Up:
                    valueUp();
                    m->Event = (u32)EventSrc::NONE;
                    return true;
                case (u32)KeyCodes::Down:
                    valueDown();
                    m->Event = (u32)EventSrc::NONE;
                    return true;
                case (u32)KeyCodes::ESC:
                    inFocus = false;
                    m->Event = (u32)EventSrc::NONE;
                    return true;
                }
            }
            return false;
        case (u32)EventSrc::TIMER:
                blinkCursor();
                return false;
    }
    return false;
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
    u16 idx = Position - 1;
    char c = Fractions[idx].c;
    c = getNextSimbol(FracPossibleValues, c);
    if (c) {
        Fractions[idx].c = c;
    }
}
void TNumericEdit::downFraction(void) {
    u16 idx = Position - 1;
    char c = Fractions[idx].c;
    c = getPrevSimbol(FracPossibleValues, c);
    if (c) {
        Fractions[idx].c = c;
    }
}

void TNumericEdit::shiftCursorLeft(void) {
    ToggleCursor = true;
    ToggleCursorDelay = NE_CURSOR_DELAY;
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
    ToggleCursor = true;
    ToggleCursorDelay = NE_CURSOR_DELAY;
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
    if (inFocus) {
        ToggleCursorDelay = (ToggleCursorDelay)
            ? --ToggleCursorDelay
            : (ToggleCursor = !ToggleCursor, NE_CURSOR_DELAY);
    }
    else {
        ToggleCursorDelay = NE_CURSOR_DELAY;
        ToggleCursor = false;
    }
}

void  TNumericEdit::view(void) {//вывести строку на экране
    TColorScheme ColorScheme = PrimaryColor;
    outCaption(ColorScheme);
}

s16 TNumericEdit::getCaptionLeftPosition(void) {
    u8 ResultLen = 0;

    /*тут выделятся числа после запятой*/
    for (auto& e : Integers) {
        if (e.sig) {
            ResultStr[ResultLen++] = e.c;
        }
    }
    /*тут выделится только запятая*/
    ResultStr[ResultLen++] = '.';

    /*тут выделятся числа после запятой*/
    for (auto& e : Fractions) {
        if (e.sig) {
            ResultStr[ResultLen++] = e.c;
        }
    }
    TTextSizes CharSizes = TMCUFonts::getCharArraySizes(ResultStr.data(), ResultLen, Font);

    s16 Left = ElementRect.Left;
    if (Style & (int)LabelsStyle::TEXT_ALIGN_CENTER) {
        Left = (ElementRect.Width - CharSizes.width) / 2;
    }
    return Left;
}

void TNumericEdit::outCaption(TColorScheme& ColorScheme) {
    s16 Top = ElementRect.Top;

    TTextSizes CharSize;
    s16 cTop = Top;
    s16 cLeft = getCaptionLeftPosition();

    u16 height = TMCUText::setFont(Font);
    u16 Count = Integers.size();
    ColorScheme = PrimaryColor;

    while (Count--) {
        TCharSignificance e = Integers[Count];
        if (e.sig) {
            if (Position < 0) {
                s16 pos = -(Count+1);
                ColorScheme = (pos == Position)
                    ? (ToggleCursor)
                        ? SelectedColor
                        : PrimaryColor
                    : PrimaryColor;
            }
            CharSize = TMCUFonts::getCharSizes(e.c, Font);
            TGrahics::fillRect({ cLeft, cTop , CharSize.width, CharSize.height, ColorScheme.BackGround });
            TGrahics::putChar(e.c, (u16&) cLeft, cTop, ColorScheme.Color);
        }
    }
    /*тут выделится только запятая*/
    ColorScheme = (Position == 0)
        ? (ToggleCursor)
            ? SelectedColor
            : PrimaryColor
        : PrimaryColor;
    CharSize = TMCUFonts::getCharSizes('.', Font);
    TGrahics::fillRect({ cLeft, cTop , CharSize.width, CharSize.height, ColorScheme.BackGround });// (u16)((Position == 0) ? 1 : 0)});
    TGrahics::putChar('.', (u16&)cLeft, cTop, ColorScheme.Color);// (Position == 0) ? 0 : 1);

    /*тут выделятся числа после запятой*/
    Count = 0;
    for (auto& e : Fractions) {
        Count++;
        if (e.sig) {
            if (Position > 0) {
                s16 pos = (Count);
                ColorScheme = (pos == Position)
                    ? (ToggleCursor)
                        ? SelectedColor
                        : PrimaryColor
                    : PrimaryColor;
            }
            else {
                ColorScheme = PrimaryColor;
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
    : TVisualObject({ init.focused, init.Rect })
    , PrimaryColor(init.PrimaryColor)
    , SelectedColor(init.SelectedColor)
    , Style((int)init.style | (int)LabelsStyle::TEXT_ALIGN_CENTER)
    , Font((init.font != "") ? init.font : "Verdana12")
    , Caption(init.caption)
    , TextSize(TMCUFonts::getTextSizes(Caption, Font))
    , Position(0)
    , ToggleCursor(false)
    , ToggleCursorDelay(NE_CURSOR_DELAY)
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
