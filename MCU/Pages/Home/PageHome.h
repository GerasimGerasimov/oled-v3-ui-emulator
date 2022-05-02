#ifndef T_PAGE_HOME_H
#define T_PAGE_HOME_H

#include "Pages.h"
#include "TComponentListVertical.h"
#include "LinkedTagLabel.h"

class TPageHome : public TPage
{
public:
    virtual void view();//вывести объект на экране
    virtual const u16 getHeight(void) { return 0; };
    void clear();//очистит список
    bool ProcessMessage(TMessage* m);//обработчик сообщений
    TPageHome(std::string Name);//конструктор
    ~TPageHome();//деструктор
private:
    /*
  {"Uref", "Напряжение задания", "kV", 0x000c, (TWORD+SByte_2), &FLASH_DATA.Koef[2], 0, 2, 0},
  {"Iref", "Ток задания", "mA", 0x000e, (TWORD+SByte_2), &FLASH_DATA.Koef[1], 0, 1, 0},
  {"UoutAve", "Среднее значение выходного напряжения", "kV", 0x002c, (TWORD+SByte_2), &FLASH_DATA.Koef[2], 0, 2, 0},
  {"IoutAve", "Среднее значение выходного напряжения", "mA", 0x002e, (TWORD+SByte_2), &FLASH_DATA.Koef[1], 0, 1, 0},
  {"SparkFrq", "Частота искр", "pcs", 0x0026, (TWORD+SByte_2), &FLASH_DATA.Koef[2], 0, 2, 0},
  {"Out", "Сигнал управления преобразователем", "%", 0x0010, (TWORD+SByte_2), &FLASH_DATA.Koef[2], 0, 2, 0},
    //EFI2.2, 165
  {"IinAve", "Входной ток", "A", 0x002A, (TWORD+SByte_2), &FLASH_DATA.Koef[1], 0, 1, 1},
*/
    TComponentListVertical* MainMenu;
    TLinkedTagLabel* pLTagUref;
    TLinkedTagLabel* pLTagIref;
    TLinkedTagLabel* pLTagUoutAve;
    TLinkedTagLabel* pLTagIoutAve;
    TLinkedTagLabel* pLTagSparkFrq;
    TLinkedTagLabel* pLTagOut;
    TLinkedTagLabel* pLTagIinAve;
    void goToCountersPage(int a);
};

#endif