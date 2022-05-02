#include "PageHome.h"
#include "Router.h"

static u32 COUNT = 0;

void TPageHome::view() {
    COUNT++;
    std::string scount = std::to_string(COUNT);
    //pLabel2->setCaption(scount);
    //pLabel4->setCaption(scount);
    MainMenu->view();
};

void TPageHome::clear() {
}

bool TPageHome::ProcessMessage(TMessage* m) {
    switch (m->Event) {
        case KEYBOARD: {
            switch (m->p1) {
            case kbESC:
                TRouter::goBack();
                break;
            }
        }
    }

    for (auto& element : List) {
        element->ProcessMessage(m);
    }
    return false;
};

void TPageHome::goToCountersPage(int a) {
    TRouter::setActivePage("Counters");
}

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
TPageHome::TPageHome(std::string Name)
    :TPage(Name) {
    TLabelInitStructure LabelInit;
    LabelInit.style = LabelsStyle::LS_DINAMIC;
    LabelInit.Rect = { 10, 10, 10, 10 };
    LabelInit.caption = "Counters>";
    LabelInit.focused = true;
    //pLabel1 = new TLinkLabel("Counters",LabelInit);
    //pLabel1->onEnterPressed = [this](int arg) { goToCountersPage(arg); };

    MainMenu = new TComponentListVertical({});// pLabel1, pLabel2, pLabel3,
                                            //pLabel4, pLabel5, pLabel6,
                                            //pLabel7, pLabel8, pLabel9 });
    /*
    TLinkedTagLabel* pLTagUref;
    TLinkedTagLabel* pLTagIref;
    TLinkedTagLabel* pLTagUoutAve;
    TLinkedTagLabel* pLTagIoutAve;
    TLinkedTagLabel* pLTagSparkFrq;
    TLinkedTagLabel* pLTagOut;
    TLinkedTagLabel* pLTagIinAve;
    */
    AddList({ MainMenu });
};

TPageHome::~TPageHome() {
};
