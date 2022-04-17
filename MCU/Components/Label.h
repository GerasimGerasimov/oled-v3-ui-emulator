#ifndef LABEL_H
#define LABEL_H

#include <string>
#include "common.h"
#include "fonts.h"

//строка текста
class TLabel : public TVisualObject
{
public:
    const FONT_INFO* font;
    u16 TextColor;//цвет текста (0-чёрный, 1-белый)
    u16 FoneColor;//цвет фона (0-чёрный, 1-белый) (закрашенный)
    void View();//вывести строку на экране
    void SetCaption(std::string NewCaption);//изменить текст в строке передав её адрес
    TLabel(std::string caption = "");//конструктор
    ~TLabel();//деструктор
private:
    std::string Caption;//строка требуется контролировать память выделенную строке    
};

#endif