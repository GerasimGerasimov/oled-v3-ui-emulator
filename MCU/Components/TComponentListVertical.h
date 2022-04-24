#ifndef MENU_H
#define MENU_H

#include <string>
#include <vector>
#include "common.h"
#include "stm32f4xx.h"
#include "msg.h"
#include "graphics.h"

class TComponentListVertical : public TVisualObject 
{
  public:
    bool isOpen;
    //с какой по какую строку меню выводить, если кол-во строк не помещаетс€ на дисплее
    u16 FocusLine;//строка наход€ща€с€ в фокусе
    u16 FirstPosition;//перва€ отображаема€ строка начинаю выводить с неЄ
    u16 LastPosition; //последн€€ отображаема€ строка
    virtual void view(void);//вывести объект на экране
    virtual u16 getHeight(void);
    void Add(TVisualObject* pVisualObject);//добавить объект в список
    void AddList(std::vector <TVisualObject*> Source);//добавить список объектов в список
    void Clear();//очистит список
    void ProcessMessage(TMessage* m);//обработчик сообщений
    TComponentListVertical(std::vector <TVisualObject*> Source = {});//конструктор
    ~TComponentListVertical();//деструктор
    const u16 ItemsCount() const;
  private:
    std::vector <TVisualObject*> List;
    u16 GetViewObjectsCount();//кол-во объектов умещающихс€ в высоту меню от FirstPosition до нижнего кра€
    //u16 Items;//количество объектов в списке
};

#endif