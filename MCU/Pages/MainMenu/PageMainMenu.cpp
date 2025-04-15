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
            new TLinkLabel("�������� ���������", "Home",LabelInit),
            new TLinkLabel("���������������", "SelfExc", LabelInit),
            new TLinkLabel("������� ���� ������", "ControlSettings", LabelInit),
            new TLinkLabel("�������� ���������", "Sensors", LabelInit),
            new TLinkLabel("����������", "Ready", LabelInit),
            new TLinkLabel("������", "Alarms", LabelInit),
            new TLinkLabel("��������������", "Warnings", LabelInit),
            new TLinkLabel("���������� �����", "DIn", LabelInit),
            new TLinkLabel("���������� ������", "DOut", LabelInit),
            new TLinkLabel("���������������", "Converter", LabelInit),
            new TLinkLabel("���������� ��������", "ReactivePower", LabelInit),

            new TLinkLabel("������������ �����", "CurrentLim", LabelInit),
            new TLinkLabel("������������ ����������", "VoltageLim", LabelInit),
            new TLinkLabel("������������ ��������", "PowerLim", LabelInit),
            new TLinkLabel("��������� �����������", "InitExcitation", LabelInit),
            new TLinkLabel("�������� ���� �������", "ControlVoltageStator", LabelInit),
            new TLinkLabel("������������ ����������", "RegulatorKoeff", LabelInit),
            new TLinkLabel("������������� ��������", "InsulResist", LabelInit),
           })
    });
};

TPageMainMenu::~TPageMainMenu() {
};
