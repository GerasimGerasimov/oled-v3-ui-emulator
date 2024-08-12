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
            new TLinkLabel("Главный экран", "Home",LabelInit),
            new TLinkLabel("Готовность", "Ready", LabelInit),
            new TLinkLabel("Предупреждения", "Warnings", LabelInit),
            new TLinkLabel("Аварии", "Alarms", LabelInit),
            new TLinkLabel("Пуск", "BasicSettings", LabelInit),
            new TLinkLabel("Напряжение статора", "StatorVoltage", LabelInit),
            new TLinkLabel("Мощность", "Power", LabelInit),
            new TLinkLabel("Опробование", "Testing", LabelInit),
            new TLinkLabel("Выпрямитель", "Rectifier", LabelInit),
            new TLinkLabel("Контроль изоляции", "ControlSettings",LabelInit),
            new TLinkLabel("Защиты выпрямителя", "RectifierProtection",LabelInit),
            new TLinkLabel("Защиты ротора", "RotorProtection",LabelInit),
            new TLinkLabel("Защиты статора", "StatorProtection",LabelInit),
            new TLinkLabel("Ограничители задания", "TaskLimit",LabelInit),
            new TLinkLabel("Ограничители реактивной мощности", "ReactPowerLimit",LabelInit),
            new TLinkLabel("Настройки ПИД регулятора", "RegulatorSettings", LabelInit),
            new TLinkLabel("Дискретные входы", "DInput", LabelInit),
            new TLinkLabel("Дискретные выходы", "DOutput", LabelInit),
           })
    });
};

TPageMainMenu::~TPageMainMenu() {
};
