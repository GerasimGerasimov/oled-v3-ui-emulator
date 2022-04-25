#include "app.h"
#include <string>
#include "graphics.h"
#include "display_driver.h"

#include "PageMainMenu.h"
#include "TComponentListVertical.h"
#include "Label.h"

TComponentListVertical* MainMenu;
TLabelInitStructure LabelInit;
TLabel* pLabel1;
TLabel* pLabel2;
TLabel* pLabel3;
TLabel* pLabel4;
TLabel* pLabel5;

TPageMainMenu* PageMainMenu;


void App::init(void) {
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

    PageMainMenu = new TPageMainMenu(false, { MainMenu });
}

static u32 COUNT = 0;

void App::run(void) {

    COUNT++;
    std::string scount = std::to_string(COUNT);

    pLabel1->setCaption(scount);
    pLabel4->setCaption(scount);
    MainMenu->view();

    TDisplayDriver::out();
}