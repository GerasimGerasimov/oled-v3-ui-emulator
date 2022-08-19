#ifndef NUMERIC_EDIT_H
#define NUMERIC_EDIT_H

#include <string>
#include "common.h"
#include "graphics.h"
#include "Label.h"
#include <array>

typedef struct {
    char c;
    bool sig;
} TCharSignificance;

class TNumericEdit : public TVisualObject {
public:
    virtual void view(void);//вывести строку на экране
    virtual const u16 getHeight(void);
    void setCaption(std::string caption);
    bool ProcessMessage(TMessage* m);
    TTextSizes getSize(void);
    TNumericEdit(TLabelInitStructure init);//конструктор
    ~TNumericEdit();//деструктор
protected:
    std::string Font;
    std::string Caption;
    TTextSizes TextSize;
    TColorScheme PrimaryColor; //основная цветовая схема 
    TColorScheme SelectedColor;//цветовая схема при выделении
    int Style;
    void fillBackGround(TColorScheme& ColorScheme);
    void outCaption(TColorScheme& ColorScheme);
    void blinkCursor(void);
    void shiftCursorLeft(void);
    void shiftCursorRight(void);
    int Position;//минус всё что слева от запятой, ноль на месте запятой, положительные всё что дробная часть
    std::array<TCharSignificance,4> Integers;
    std::array<TCharSignificance, 2> Fractions;
};

#endif