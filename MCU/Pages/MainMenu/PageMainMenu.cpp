#include "PageMainMenu.h"
#include "Router.h"
#include <functional>

static u32 COUNT = 0;

void TPageMainMenu::view() {
    COUNT++;
    std::string scount = std::to_string(COUNT);
    pLabel2->setCaption(scount);
    pLabel4->setCaption(scount);
    MainMenu->view();
};

void TPageMainMenu::clear() {
}

bool TPageMainMenu::ProcessMessage(TMessage* m) {
    switch (m->Event) {
        case KEYBOARD: {
            switch (m->p1) {
            case (u32)KeyCodes::ESC:
                TRouter::setActivePage("Home", NULL);//TRouter::goBack();
                break;
            }
        }
    }

    for (auto& element : List) {
        element->ProcessMessage(m);
    }
    return false;
};

void TPageMainMenu::goToCountersPage(int a) {
    TRouter::setActivePage("Counters", NULL);
}

TPageMainMenu::TPageMainMenu(std::string Name)
    :TPage(Name) {
    TLabelInitStructure LabelInit;
    LabelInit.style = LabelsStyle::LS_DINAMIC;
    LabelInit.Rect = { 10, 10, 10, 10 };
    LabelInit.caption = "Counters>";
    LabelInit.focused = true;
    pLabel1 = new TLinkLabel("Counters",LabelInit);
    pLabel1->onEnterPressed = [this](int arg) { goToCountersPage(arg); };
    LabelInit.focused = false;
    LabelInit.caption = "2 Привет";
    pLabel2 = new TLabel(LabelInit);
    LabelInit.caption = "3 Привет";
    LabelInit.font = "MSSansSerifBold14";
    pLabel3 = new TLabel(LabelInit);
    LabelInit.caption = "4 Привет";
    pLabel4 = new TLabel(LabelInit);
    LabelInit.caption = "5 Привет";
    pLabel5 = new TLabel(LabelInit);
    LabelInit.caption = "6 Привет";
    LabelInit.font = "Verdana12";
    pLabel6 = new TLabel(LabelInit);
    LabelInit.caption = "7 Привет";
    pLabel7 = new TLabel(LabelInit);
    LabelInit.caption = "8 Привет";
    pLabel8 = new TLabel(LabelInit);
    LabelInit.caption = "9 Привет";
    pLabel9 = new TLabel(LabelInit);
    MainMenu = new TComponentListVertical({ pLabel1 , pLabel2 , pLabel3, 
                                            pLabel4, pLabel5, pLabel6,
                                            pLabel7, pLabel8, pLabel9 });
    AddList({ MainMenu });
};

TPageMainMenu::~TPageMainMenu() {
};
