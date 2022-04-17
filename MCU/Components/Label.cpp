#include "Label.h"

#include "graphics.h"

//класс "строка текста"
void  TLabel::View() {//вывести строку на экране
  /*TTextProperty TextProperty = {
    //границы прямоугольника куда требуется вписать текст
    Left,//u16 MinLeft;
    Top,//u16 MinTop;
    Left+Width,//u16 MaxRight;
    Top+Height,//u16 MaxBottom;
    //начальные координаты текста (относительно прямоугольника куда тербуется вписать текст)
    //т.е. они могут быть и отрицательными
    0,//s16 X;
    0,//s16 Y;
    //выравнивание текста
    //0 - прижать текст к левой границе ограничивающего прямоугольника
    //1 - прижать текст к правой границе ограничивающего прямоугольника
    //2 - центровать между левой и правой границами ограничивающего прямоугольника
    0,//u8 Align;
    //цвет текста
    TextColor,//u8 Color;
    //шрифт выводимого символа/строки
    font,//FONT_INFO* font;
  };*/
    u8 i = 0;
    u8 j = 0;
    u8 c;

    u16 fone_color = NEG_COLOR;
    u16 text_color = BASIC_COLOR;

    if (Focus) {
        fone_color = BASIC_COLOR;
        text_color = NEG_COLOR;
    }

    //TextProperty.Color = text_color;
    TFillRect rect{ Left, Top, MAX_RIGHT, Height, fone_color };
    TGrahics::fillRect(rect);
    TTextProps textProps{ Left, Top, text_color, fone_color };
    TGrahics::outText(textProps, Caption);
}

u16 GetStrWidth(std::string s, const FONT_INFO* font) {//возвращает ширину строки
    u16 w = 0;
    char* pC = (char*)s.c_str();
    while (*pC++ != 0) {
        w += font->charInfo[*pC - 0x21].widthBits;
    }
    return w;
}

#define max_str_size 0x100 //памяти мало, делаю ограничение на длину строки

u16 GetStrLength(char* s) {//возвращает длину строки
    u16 l = 0;
    while (*s++ != 0) {
        l++;
        //если строка больше 255 символов, то ограничить её в 255
        //зарезервировав 255-й быйт для "0"
        if (l == max_str_size) break;
    }
    return l;
}

void TLabel::SetCaption(std::string NewCaption) {//добавить/изменить текст в строке
    Caption = NewCaption;
}

TLabel::TLabel(std::string caption) {//конструктор
    Focus = false;
    //инициализация содержимого строки
    SetCaption((caption != "") ? caption : "default");
    //цветa по умолчению
    TextColor = BASIC_COLOR;
    FoneColor = NEG_COLOR;
    //размеры лейбла
    Left = 80;  //
    Top = 0;   //
    //фонт по умолчанию
    font = &FontInfomSReferenceSansSerif6pt;
    Height = font->CharHeight;//высота строки = высота символа в данном шрифте
    Width = GetStrWidth(Caption, font); //ширина строки = сумма ширин символов в строке
    //
}

TLabel::~TLabel() {//деструктор
}
