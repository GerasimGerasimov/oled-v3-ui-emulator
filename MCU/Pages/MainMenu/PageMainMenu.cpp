#include "PageMainMenu.h"
#include "Router.h"
#include <functional>

void TPageMainMenu::view() {
    Container->view();
};

bool TPageMainMenu::ProcessMessage(TMessage* m) {
    switch (m->Event) {
        case (u32)EventSrc::KEYBOARD: {
            switch (m->p1) {
            case (u32)KeyCodes::ESC:
                TRouter::setTask({ false, "Home", nullptr });
                break;
            }
        }
    }

    for (auto& element : List) {
        element->ProcessMessage(m);
    }
    return false;
};

TPageMainMenu::TPageMainMenu(std::string Name)
    :TPage(Name) {
    TVerticalContainerProps pLabelsProps = { true };
    TLabelInitStructure LabelInit;
    LabelInit.style = LabelsStyle::WIDTH_DINAMIC;
    LabelInit.Rect = { 10, 10, 10, 10 };
    AddList({
        Container = new TVerticalContainer(pLabelsProps, {
            new TLinkLabel("Основные параметры", "Home",LabelInit),
            //new TLinkLabel("Статус работы", "OperateStatus", LabelInit),
            new TLinkLabel("Уставки возбуждения", "BasicSettings", LabelInit),
            new TLinkLabel("Аварии", "Alarms", LabelInit),
            //new TLinkLabel("Предупреждения", "Warnings", LabelInit),
            new TLinkLabel("Индикаторы", "Sensors", LabelInit),
            new TLinkLabel("Дискретные входы", "DIn", LabelInit),
            new TLinkLabel("Дискретные выходы", "DOut", LabelInit),
            new TLinkLabel("Питающая сеть", "PowerSupply", LabelInit),
            new TLinkLabel("Уставки защит", "BasicProtectionsSettings", LabelInit),
            new TLinkLabel("Ограничители", "Limiters", LabelInit),
            new TLinkLabel("Уставки питания", "PowerSettings", LabelInit),
            new TLinkLabel("Уставки регулятора", "RegulatorSettings", LabelInit)
            //new TLinkLabel("Очистка. Уставки", "CleanSettings", LabelInit),
           })
    });
};

TPageMainMenu::~TPageMainMenu() {
};
