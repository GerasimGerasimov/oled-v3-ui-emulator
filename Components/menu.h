#ifndef MENU_H
#define MENU_H

#include <string>
#include <vector>
#include "stm32f4xx.h"
#include "msg.h"
#include "fonts.h"

class TVisualObject{//базовый класс визуальных объектов
  public:
    //нахождение визуального объекта в фокусе
    bool Focus;//false-не в фокусе true-в фокусе
    //область вывода (откуда начинать и контроль границ)
    s16 Left;  //
    s16 Top;   //
    u16 Height;//
    u16 Width; //
    virtual void View();//вывести объект на экране
    TVisualObject ();//конструктор
    virtual ~TVisualObject();//деструктор
};

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

class TMenu : public TVisualObject 
{
  public:
    bool isOpen;
    TLabel * Caption;//строка требуется контролировать память выделенную строке 
    //область вывода (откуда начинать и контроль границ)
    u16 Left;  //
    u16 Top;   //
    u16 Height;//
    u16 Width; //
    //с какой по какую строку меню выводить, если кол-во строк не помещается на дисплее
    u16 FocusLine;//строка находящаяся в фокусе
    u16 FirstPosition;//первая отображаемая строка начинаю выводить с неё
    u16 LastPosition; //последняя отображаемая строка
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
    u16 GetViewObjectsCount();//кол-во объектов умещающихся в высоту меню от FirstPosition до нижнего края
    //u16 Items;//количество объектов в списке
};

#endif