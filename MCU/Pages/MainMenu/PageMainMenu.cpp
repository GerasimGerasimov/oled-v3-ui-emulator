#include "PageMainMenu.h"
#include "Router.h"
#include <functional>

void TPageMainMenu::view() {
    Container->view();
};

void TPageMainMenu::clear() {
}

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
    TLabelInitStructure LabelInit;
    LabelInit.style = LabelsStyle::WIDTH_DINAMIC;
    LabelInit.Rect = { 10, 10, 10, 10 };
    AddList({
        Container = new TVerticalContainer({
            new TLinkLabel("�������� ���������", "Home",LabelInit),
            new TLinkLabel("��������������", "Home", LabelInit),
            new TLinkLabel("������", "Alarms", LabelInit),
            new TLinkLabel("�������� ������� ������", "Home", LabelInit),
            new TLinkLabel("������� �����", "Home", LabelInit),
            new TLinkLabel("������� ������ �������", "Home", LabelInit),
            new TLinkLabel("������� ������� ������", "Home", LabelInit),
            new TLinkLabel("������� ���", "Home", LabelInit),
            new TLinkLabel("������ ������ ���", "Home", LabelInit),
            new TLinkLabel("������ �������� ���", "Home", LabelInit),
            new TLinkLabel("������� �����������", "Home", LabelInit),
            new TLinkLabel("������ ��������", "Home", LabelInit),
            new TLinkLabel("��������� ������", "Home", LabelInit)
           })
    });
};

TPageMainMenu::~TPageMainMenu() {
};
