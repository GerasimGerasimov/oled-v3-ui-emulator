#ifndef T_PAGE_HOME_H
#define T_PAGE_HOME_H

#include "Pages.h"
#include "TComponentListVertical.h"
#include "LinkedTagLabel.h"

class TPageHome : public TPage
{
public:
    virtual void view();//������� ������ �� ������
    virtual const u16 getHeight(void) { return 0; };
    void clear();//������� ������
    bool ProcessMessage(TMessage* m);//���������� ���������
    TPageHome(std::string Name);//�����������
    ~TPageHome();//����������
private:
    /*
  {"Uref", "���������� �������", "kV", 0x000c, (TWORD+SByte_2), &FLASH_DATA.Koef[2], 0, 2, 0},
  {"Iref", "��� �������", "mA", 0x000e, (TWORD+SByte_2), &FLASH_DATA.Koef[1], 0, 1, 0},
  {"UoutAve", "������� �������� ��������� ����������", "kV", 0x002c, (TWORD+SByte_2), &FLASH_DATA.Koef[2], 0, 2, 0},
  {"IoutAve", "������� �������� ��������� ����������", "mA", 0x002e, (TWORD+SByte_2), &FLASH_DATA.Koef[1], 0, 1, 0},
  {"SparkFrq", "������� ����", "pcs", 0x0026, (TWORD+SByte_2), &FLASH_DATA.Koef[2], 0, 2, 0},
  {"Out", "������ ���������� ����������������", "%", 0x0010, (TWORD+SByte_2), &FLASH_DATA.Koef[2], 0, 2, 0},
    //EFI2.2, 165
  {"IinAve", "������� ���", "A", 0x002A, (TWORD+SByte_2), &FLASH_DATA.Koef[1], 0, 1, 1},
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