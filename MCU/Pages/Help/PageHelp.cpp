#include "PageHelp.h"
#include "Router.h"
#include "parameters.h"

void TPageHelp::view() {
    MainMenu->view();
};

void TPageHelp::clear() {
}

void TPageHelp::onOpen() {
    /*TODO �� ���� ���������� ������������ ���� ��� �����, TParameter ��� �������� ��� �� ����������*/
    TParameter* p = (TParameter*)props;
    pHeader->setCaption(p->getName());
}

bool TPageHelp::ProcessMessage(TMessage* m) {
    switch (m->Event) {
        case KEYBOARD: {
            switch (m->p1) {
            case (u32)KeyCodes::ESC :
                TRouter::goBack();
                break;
            }
        }
    }

    for (auto& element : List) {
        element->ProcessMessage(m);
    }
    return false;
};

TPageHelp::TPageHelp(std::string Name)
    :TPage(Name) {
    TLabelInitStructure LabelInit;
    LabelInit.style = (LabelsStyle)((u32) LabelsStyle::LS_FIXED | (u32) LabelsStyle::ALIGN_CENTER);
    LabelInit.Rect = { 10, 10, 10, 10 };
    LabelInit.focused = true;

    LabelInit.caption = "---";
    pHeader = new TLabel(LabelInit);

    pText = new TWrappedText(LabelInit);


    MainMenu = new TComponentListVertical({ pHeader, pText });

    AddList({ MainMenu });
};

TPageHelp::~TPageHelp() {
};
