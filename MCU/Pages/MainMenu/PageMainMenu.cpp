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
            new TLinkLabel("Аварии", "Alarms", LabelInit),
            new TLinkLabel("Предупреждения", "Warnings", LabelInit),
            new TLinkLabel("Дополнительные данные", "AdditionalData", LabelInit),
            new TLinkLabel("Флаги работы", "WorkFlags", LabelInit),
            new TLinkLabel("Дискретные входы", "DIn", LabelInit),
            new TLinkLabel("Дискретные выходы", "DOut", LabelInit),
            //new TLinkLabel("Датчики", "Sensors", LabelInit),
            new TLinkLabel("Уставки работы", "BasicSettings", LabelInit),
            new TLinkLabel("Уставки защиты", "BasicProtectionsSettings", LabelInit),
            new TLinkLabel("Уставки времени", "CommunicationSettings", LabelInit),
            //new TLinkLabel("Настройки панели", "PanelSettings", LabelInit),
            //new TLinkLabel("Очистка. Уставки", "CleanSettings", LabelInit),
           })
    });
};

TPageMainMenu::~TPageMainMenu() {
};
