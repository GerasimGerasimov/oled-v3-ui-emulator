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
            new TLinkLabel("������� �����", "BasicSettings", LabelInit),
            new TLinkLabel("��������� �������", "Alarms", LabelInit),
            new TLinkLabel("���������� �����", "DInput", LabelInit),
            new TLinkLabel("���������� ������", "DOutput", LabelInit),

            new TLinkLabel("������� �����", "PowerSection", LabelInit),
            new TLinkLabel("������������ �����", "GeneratorMode", LabelInit),
            new TLinkLabel("��� �������", "StatorCurrent", LabelInit),
            new TLinkLabel("���������� �������", "StatorVoltage", LabelInit),
            new TLinkLabel("������ �����������", "Excitation", LabelInit),
            new TLinkLabel("�������� ��������", "ControlSettings",LabelInit),
            new TLinkLabel("����������� ����", "CurrentLimit",LabelInit),
            new TLinkLabel("�������������� �����", "AutoMode",LabelInit),
            new TLinkLabel("cos ���������", "CosSetting",LabelInit),
            new TLinkLabel("��������� �����", "NetWorkSettings",LabelInit),
            new TLinkLabel("������� ������", "CurrentProtection",LabelInit),
            new TLinkLabel("����� ����", "FieldBreak",LabelInit),
            new TLinkLabel("��������� ����", "RegulatorSettings", LabelInit),
            new TLinkLabel("����������", "Sliding", LabelInit),
            new TLinkLabel("�����������", "Testing", LabelInit),

            //new TLinkLabel("������� ���", "Home", LabelInit),
            //new TLinkLabel("������ ������ ���", "Home", LabelInit),
            //new TLinkLabel("������ �������� ���", "Home", LabelInit),
            //new TLinkLabel("������ ��������", "Home", LabelInit),
           })
    });
};

TPageMainMenu::~TPageMainMenu() {
};
