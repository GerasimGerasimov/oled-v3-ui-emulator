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
            new TLinkLabel("Самовозбуждение", "SelfExc", LabelInit),
            new TLinkLabel("Задания авто режима", "ControlSettings", LabelInit),
            new TLinkLabel("Выходные параметры", "Sensors", LabelInit),
            new TLinkLabel("Готовность", "Ready", LabelInit),
            new TLinkLabel("Аварии", "Alarms", LabelInit),
            new TLinkLabel("Предупреждения", "Warnings", LabelInit),
            new TLinkLabel("Дискретные входы", "DIn", LabelInit),
            new TLinkLabel("Дискретные выходы", "DOut", LabelInit),
            new TLinkLabel("Преобразователь", "Converter", LabelInit),
            new TLinkLabel("Реактивная мощность", "ReactivePower", LabelInit),

            new TLinkLabel("Ограничетели токов", "CurrentLim", LabelInit),
            new TLinkLabel("Ограничетели напряжений", "VoltageLim", LabelInit),
            new TLinkLabel("Ограничетели мощности", "PowerLim", LabelInit),
            new TLinkLabel("Начальное возбуждение", "InitExcitation", LabelInit),
            new TLinkLabel("Контроль напр статора", "ControlVoltageStator", LabelInit),
            new TLinkLabel("Коэффициенты регулятора", "RegulatorKoeff", LabelInit),
            new TLinkLabel("Сопротивление изоляции", "InsulResist", LabelInit),
           })
    });
};

TPageMainMenu::~TPageMainMenu() {
};
