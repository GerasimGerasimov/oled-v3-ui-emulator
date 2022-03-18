#ifndef MENU_H
#define MENU_H

#include <string>
#include <vector>
#include "common.h"
#include "stm32f4xx.h"
#include "msg.h"
#include "fonts.h"
#include "Label.h"

class TVisualObjectsList{//список визуальных объектов (контейнер)
  public:
    //область вывода (откуда начинать и контроль границ)
    u16 Left;  //
    u16 Top;   //
    u16 Height;//
    u16 Width; //
    u16 Count;//количество объектов в списке
    void View();//вывести объект на экране
    void Add(TVisualObject* pVisualObject);//добавить объект в список
    void Clear();//очистит список
    TVisualObjectsList ();//конструктор
    virtual ~TVisualObjectsList();//деструктор
  private:
    std::vector <TVisualObject*> List;
};

class TMenu : public TVisualObject 
{
  public:
    bool isOpen;
    TLabel * Caption;//строка требуетс€ контролировать пам€ть выделенную строке 
    //область вывода (откуда начинать и контроль границ)
    u16 Left;  //
    u16 Top;   //
    u16 Height;//
    u16 Width; //
    //с какой по какую строку меню выводить, если кол-во строк не помещаетс€ на дисплее
    u16 FocusLine;//строка наход€ща€с€ в фокусе
    u16 FirstPosition;//перва€ отображаема€ строка начинаю выводить с неЄ
    u16 LastPosition; //последн€€ отображаема€ строка
    void View();//вывести объект на экране
    void Add(TVisualObject* pVisualObject);//добавить объект в список
    void AddList(std::vector <TVisualObject*> Source);//добавить список объектов в список
    void Clear();//очистит список
    void ProcessMessage(TMessage* m);//обработчик сообщений
    TMenu(std::string сaption, bool isOpenState, std::vector <TVisualObject*> Source = {});//конструктор
    ~TMenu();//деструктор
    const u16& ItemsCount() const;
  private:
    std::vector <TVisualObject*> List;
    u16 GetViewObjectsCount();//кол-во объектов умещающихс€ в высоту меню от FirstPosition до нижнего кра€
    //u16 Items;//количество объектов в списке
};

#endif