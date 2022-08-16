#include "PageMainMenu.h"
#include "Router.h"
#include <functional>

void TPageMainMenu::view() {
    MainMenu->view();
};

void TPageMainMenu::clear() {
}

bool TPageMainMenu::ProcessMessage(TMessage* m) {
    switch (m->Event) {
        case (u32)EventSrc::KEYBOARD: {
            switch (m->p1) {
            case (u32)KeyCodes::ESC:
                TRouter::setTask({ false, "Home", NULL });
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
        MainMenu = new TComponentListVertical({
            new TLinkLabel("�������� ���������", "Home",LabelInit),
            new TLinkLabel("��������������", "Home", LabelInit),
            new TLinkLabel("������", "Home", LabelInit),
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
