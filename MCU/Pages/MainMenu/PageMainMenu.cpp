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
            new TLinkLabel("Уставки пуска", "BasicSettings", LabelInit),
            new TLinkLabel("Аварийные сигналы", "Alarms", LabelInit),
            new TLinkLabel("Дискретные входы", "DInput", LabelInit),
            new TLinkLabel("Дискретные выходы", "DOutput", LabelInit),

            new TLinkLabel("Силовая часть", "PowerSection", LabelInit),
            new TLinkLabel("Генераторный режим", "GeneratorMode", LabelInit),
            new TLinkLabel("Ток статора", "StatorCurrent", LabelInit),
            new TLinkLabel("Напряжение статора", "StatorVoltage", LabelInit),
            new TLinkLabel("Подача возбуждения", "Excitation", LabelInit),
            new TLinkLabel("Контроль изоляции", "ControlSettings",LabelInit),
            new TLinkLabel("Ограничение тока", "CurrentLimit",LabelInit),
            new TLinkLabel("Автоматический режим", "AutoMode",LabelInit),
            new TLinkLabel("cos настройка", "CosSetting",LabelInit),
            new TLinkLabel("Настройки связи", "NetWorkSettings",LabelInit),
            new TLinkLabel("Токовые защиты", "CurrentProtection",LabelInit),
            new TLinkLabel("Обрыв поля", "FieldBreak",LabelInit),
            new TLinkLabel("Настройки тока", "RegulatorSettings", LabelInit),
            new TLinkLabel("Скольжение", "Sliding", LabelInit),
            new TLinkLabel("Опробование", "Testing", LabelInit),

            //new TLinkLabel("Уставки ВАХ", "Home", LabelInit),
            //new TLinkLabel("Данные прямой ВАХ", "Home", LabelInit),
            //new TLinkLabel("Данные обратной ВАХ", "Home", LabelInit),
            //new TLinkLabel("Данные драйвера", "Home", LabelInit),
           })
    });
};

TPageMainMenu::~TPageMainMenu() {
};
