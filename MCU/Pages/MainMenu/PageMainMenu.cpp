#include "PageMainMenu.h"

static u32 COUNT = 0;

void TPageMainMenu::view() {
    COUNT++;
    //std::string scount = std::to_string(COUNT);
    //pLabel2->setCaption(scount);
    //pLabel4->setCaption(scount);
    MainMenu->view();
};

void TPageMainMenu::clear() {
}

bool TPageMainMenu::ProcessMessage(TMessage* m) {
    for (auto& element : List) {
        element->ProcessMessage(m);
    }
    return false;
};

TPageMainMenu::TPageMainMenu(std::string Name)
    :TPage(Name) {
    LabelInit.style = LabelsStyle::LS_DINAMIC;
    LabelInit.Rect = { 10, 10, 10, 10 };
    LabelInit.caption = "Counters";
    LabelInit.focused = true;
    pLabel1 = new TLinkLabel("Counters",LabelInit);
    LabelInit.focused = false;
    LabelInit.caption = "2 ������";
    pLabel2 = new TLabel(LabelInit);
    LabelInit.caption = "3 ������";
    LabelInit.font = "MSSansSerifBold14";
    pLabel3 = new TLabel(LabelInit);
    LabelInit.caption = "4 ������";
    pLabel4 = new TLabel(LabelInit);
    LabelInit.caption = "5 ������";
    pLabel5 = new TLabel(LabelInit);
    LabelInit.caption = "6 ������";
    LabelInit.font = "Verdana12";
    pLabel6 = new TLabel(LabelInit);
    LabelInit.caption = "7 ������";
    pLabel7 = new TLabel(LabelInit);
    LabelInit.caption = "8 ������";
    pLabel8 = new TLabel(LabelInit);
    LabelInit.caption = "9 ������";
    pLabel9 = new TLabel(LabelInit);
    MainMenu = new TComponentListVertical({ pLabel1 , pLabel2 , pLabel3, 
                                            pLabel4, pLabel5, pLabel6,
                                            pLabel7, pLabel8, pLabel9 });
    AddList({ MainMenu });
};

TPageMainMenu::~TPageMainMenu() {
};
