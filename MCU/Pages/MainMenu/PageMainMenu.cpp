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
            new TLinkLabel("����������", "Ready",LabelInit),
            new TLinkLabel("��������� �������", "Alarms", LabelInit),

            new TLinkLabel("���������� �����", "DInput", LabelInit),
            new TLinkLabel("���������� ������", "DOutput", LabelInit),
            new TLinkLabel("��������� ����", "Sensors", LabelInit),
            new TLinkLabel("�����������", "Excitation", LabelInit),
            new TLinkLabel("�������������� �������", "InformationSignals", LabelInit),
            new TLinkLabel("����������� ���������", "ControlParameters", LabelInit),
            //new TLinkLabel("��������������", "Warnings", LabelInit),
            new TLinkLabel("��������", "Nominal", LabelInit),
            new TLinkLabel("�����������", "BasicSettings", LabelInit),
            new TLinkLabel("������� �����", "BasicProtectionsSettings", LabelInit),
            new TLinkLabel("������� ����������", "RegulatorSettings", LabelInit),
            //new TLinkLabel("�������. �������", "CleanSettings", LabelInit),
            new TLinkLabel("�������� ����", "NetWorkSettings",LabelInit),
            new TLinkLabel("�������� ��������", "ControlSettings",LabelInit),
            new TLinkLabel("�������� ������", "ThermalProtection",LabelInit),
            //new TLinkLabel("����������", "OperateStatus", LabelInit),
            new TLinkLabel("����������", "Calibration",LabelInit),
            new TLinkLabel("��������� ������", "PanelSettings", LabelInit),
            //new TLinkLabel("������� ������� ������", "Home", LabelInit),
            //new TLinkLabel("������� ���", "Home", LabelInit),
            //new TLinkLabel("������ ������ ���", "Home", LabelInit),
            //new TLinkLabel("������ �������� ���", "Home", LabelInit),
            //new TLinkLabel("������ ��������", "Home", LabelInit),
           })
    });
};

TPageMainMenu::~TPageMainMenu() {
};
