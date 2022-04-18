#ifndef LABEL_H
#define LABEL_H

#include <string>
#include "common.h"
#include "graphics.h"

struct TColorScheme {
    u16 Color;
    u16 BackGround;
};

typedef union {
    u16	   i;
    struct {//флаги стилей
        unsigned Dinamic : 1;
        unsigned Fixed : 1;
    } bits;
} LabelStyle;//флаги управления и индикации;

struct TLabelInitStructure {
    bool focused = false;
    std::string caption = "";
    std::string font = "Verdana12";
    LabelStyle style = { 0 };
    TColorScheme PrimaryColor = { PRIMARY_COLOR , BACKGROUND_COLOR }; //основная цветовая схема 
    TColorScheme SelectedColor = { BACKGROUND_COLOR, PRIMARY_COLOR };//цветовая схема при выделении
    TElementRect Rect = { 0, 0, 64, 10 };
};

//строка текста
class TLabel : public TVisualObject {
public:
    void view();//вывести строку на экране
    void setCaption(std::string caption);//изменить текст в строке передав её адрес
    void setFont(std::string font);//изменить текст в строке передав её адрес
    TTextSizes getSize(void);
    TLabel(TLabelInitStructure init);//конструктор
    ~TLabel();//деструктор
private:
    std::string Font;
    std::string Caption;
    TColorScheme PrimaryColor; //основная цветовая схема 
    TColorScheme SelectedColor;//цветовая схема при выделении
    LabelStyle Style;
};

#endif