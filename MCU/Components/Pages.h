#ifndef PAGES_H
#define PAGES_H

#include <vector>
#include "common.h"
#include "stm32f4xx.h"
#include "msg.h"

class TPage : public TVisualObject
{
public:
    bool isOpen;
    //с какой по какую строку меню выводить, если кол-во строк не помещается на дисплее
    TVisualObject* pFocusedElement;//строка находящаяся в фокусе
    void View();//вывести объект на экране
    void Add(TVisualObject* pVisualObject);//добавить объект в список
    void AddList(std::vector <TVisualObject*> Source);//добавить список объектов в список
    void Clear();//очистит список
    void ProcessMessage(TMessage* m);//обработчик сообщений
    TPage(bool isOpenState, std::vector <TVisualObject*> Source = {});//конструктор
    ~TPage();//деструктор
private:
    std::vector <TVisualObject*> List;
    u16 GetViewObjectsCount();//кол-во объектов умещающихся в высоту меню от FirstPosition до нижнего края
};

#endif