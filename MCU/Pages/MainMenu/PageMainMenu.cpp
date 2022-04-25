#include "PageMainMenu.h"

static u32 COUNT = 0;

void TPageMainMenu::view() {
    COUNT++;
    std::string scount = std::to_string(COUNT);
    pLabel1->setCaption(scount);
    pLabel4->setCaption(scount);
    MainMenu->view();
};

void TPageMainMenu::clear() {
}

void TPageMainMenu::ProcessMessage(TMessage* m) {
};

TPageMainMenu::TPageMainMenu()
    :TPage() {
    LabelInit.caption = "Привет";
    LabelInit.style = LabelsStyle::LS_DINAMIC;
    LabelInit.focused = true;
    LabelInit.Rect = { 10, 10, 10, 10 };
    pLabel1 = new TLabel(LabelInit);
    pLabel2 = new TLabel(LabelInit);
    LabelInit.caption = "досвидания";
    LabelInit.focused = true;
    LabelInit.font = "MSSansSerifBold14";
    pLabel3 = new TLabel(LabelInit);
    pLabel4 = new TLabel(LabelInit);
    pLabel5 = new TLabel(LabelInit);
    MainMenu = new TComponentListVertical({ pLabel1 , pLabel2 , pLabel3, pLabel4, pLabel5 });
    AddList({ MainMenu });
};

TPageMainMenu::~TPageMainMenu() {
};
