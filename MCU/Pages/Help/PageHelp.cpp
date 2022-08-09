#include "PageHelp.h"
#include "Router.h"

void TPageHelp::view() {
    MainMenu->view();
};

void TPageHelp::clear() {
}

void TPageHelp::onOpen() {
    void* p = props;
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

void TPageHelp::goToTagInfoPage(int a) {
    TRouter::setActivePage("Counters", NULL);
}

TPageHelp::TPageHelp(std::string Name)
    :TPage(Name) {
    TLabelInitStructure LabelInit;
    LabelInit.style = LabelsStyle::LS_DINAMIC;
    LabelInit.Rect = { 10, 10, 10, 10 };
    LabelInit.focused = false;

    LabelInit.caption = "Uref";
    pLTagUref = new TLinkedTagLabel("U1.RAM.Uref", LabelInit);
    pLTagUref->onEnterPressed = [this](int arg) { goToTagInfoPage(arg); };


    MainMenu = new TComponentListVertical({ pLTagUref });

    AddList({ MainMenu });
};

TPageHelp::~TPageHelp() {
};
