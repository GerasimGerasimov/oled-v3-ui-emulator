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
            new TLinkLabel("������� �����", "Home",LabelInit),
            new TLinkLabel("����������", "Ready", LabelInit),
            new TLinkLabel("��������������", "Warnings", LabelInit),
            new TLinkLabel("������", "Alarms", LabelInit),
            new TLinkLabel("����", "BasicSettings", LabelInit),
            new TLinkLabel("���������� �������", "StatorVoltage", LabelInit),
            new TLinkLabel("��������", "Power", LabelInit),
            new TLinkLabel("�����������", "Testing", LabelInit),
            new TLinkLabel("�����������", "Rectifier", LabelInit),
            new TLinkLabel("�������� ��������", "ControlSettings",LabelInit),
            new TLinkLabel("������ �����������", "RectifierProtection",LabelInit),
            new TLinkLabel("������ ������", "RotorProtection",LabelInit),
            new TLinkLabel("������ �������", "StatorProtection",LabelInit),
            new TLinkLabel("������������ �������", "TaskLimit",LabelInit),
            new TLinkLabel("������������ ���������� ��������", "ReactPowerLimit",LabelInit),
            new TLinkLabel("��������� ��� ����������", "RegulatorSettings", LabelInit),
            new TLinkLabel("���������� �����", "DInput", LabelInit),
            new TLinkLabel("���������� ������", "DOutput", LabelInit),
           })
    });
};

TPageMainMenu::~TPageMainMenu() {
};
