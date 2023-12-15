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
            new TLinkLabel("Готовность", "Ready",LabelInit),
            new TLinkLabel("Аварийные сигналы", "Alarms", LabelInit),

            new TLinkLabel("Дискретные входы", "DInput", LabelInit),
            new TLinkLabel("Дискретные выходы", "DOutput", LabelInit),
            new TLinkLabel("Параметры сети", "Sensors", LabelInit),
            new TLinkLabel("Возбуждение", "Excitation", LabelInit),
            new TLinkLabel("Информационные сигналы", "InformationSignals", LabelInit),
            new TLinkLabel("Контрольные параметры", "ControlParameters", LabelInit),
            //new TLinkLabel("Предупреждения", "Warnings", LabelInit),
            new TLinkLabel("Номиналы", "Nominal", LabelInit),
            new TLinkLabel("Ограничения", "BasicSettings", LabelInit),
            new TLinkLabel("Уставки защит", "BasicProtectionsSettings", LabelInit),
            new TLinkLabel("Уставки регулятора", "RegulatorSettings", LabelInit),
            //new TLinkLabel("Очистка. Уставки", "CleanSettings", LabelInit),
            new TLinkLabel("Качество сети", "NetWorkSettings",LabelInit),
            new TLinkLabel("Контроль изоляции", "ControlSettings",LabelInit),
            new TLinkLabel("Тепловая защита", "ThermalProtection",LabelInit),
            //new TLinkLabel("Калибровки", "OperateStatus", LabelInit),
            new TLinkLabel("Калибровки", "Calibration",LabelInit),
            new TLinkLabel("Настройки панели", "PanelSettings", LabelInit),
            //new TLinkLabel("Уставки ручного режима", "Home", LabelInit),
            //new TLinkLabel("Уставки ВАХ", "Home", LabelInit),
            //new TLinkLabel("Данные прямой ВАХ", "Home", LabelInit),
            //new TLinkLabel("Данные обратной ВАХ", "Home", LabelInit),
            //new TLinkLabel("Данные драйвера", "Home", LabelInit),
           })
    });
};

TPageMainMenu::~TPageMainMenu() {
};
