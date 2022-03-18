#ifndef COMMON_VISUAL_H
#define COMMON_VISUAL_H

#include <stm32f4xx.h>

class TVisualObject {//базовый класс визуальных объектов
public:
    //нахождение визуального объекта в фокусе
    bool Focus = false;//false-не в фокусе true-в фокусе
    //область вывода (откуда начинать и контроль границ)
    s16 Left;  //
    s16 Top;   //
    u16 Height;//
    u16 Width; //
    virtual void View();//вывести объект на экране
    TVisualObject();//конструктор
    ~TVisualObject();//деструктор
};

#endif