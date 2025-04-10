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
             new TLinkLabel("Статусы", "Home",LabelInit),
            // new TLinkLabel("Статус работы", "OperateStatus", LabelInit),
             new TLinkLabel("Уставки температуры", "BasicSettings", LabelInit),
            // new TLinkLabel("Датчики", "Sensors", LabelInit),
             new TLinkLabel("Уставки времени", "TimeSettings", LabelInit),
             new TLinkLabel("Аварии", "Alarms", LabelInit),
             new TLinkLabel("Предупреждения", "Warnings", LabelInit),
             new TLinkLabel("Заводские уставки", "FactorySettings", LabelInit),
            //new TLinkLabel("Очистка. Уставки", "CleanSettings", LabelInit),
            //new TLinkLabel("Настройки связи EFi", "NetWorkSettings",LabelInit),
            //new TLinkLabel("Настройки панели", "PanelSettings", LabelInit),
            // new TLinkLabel("Калибровки", "CD", LabelInit),
           })
    });
};

TPageMainMenu::~TPageMainMenu() {
};
