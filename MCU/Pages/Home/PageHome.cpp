#include "PageHome.h"
#include "Router.h"

void TPageHome::view() {
    MainMenu->view();
};

void TPageHome::clear() {
}

bool TPageHome::ProcessMessage(TMessage* m) {
    switch (m->Event) {
        case KEYBOARD: {
            switch (m->p1) {
            case kbESC:
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

void TPageHome::goToTagInfoPage(int a) {
    TRouter::setActivePage("Counters");
}

TPageHome::TPageHome(std::string Name)
    :TPage(Name) {
    TLabelInitStructure LabelInit;
    LabelInit.style = LabelsStyle::LS_DINAMIC;
    LabelInit.Rect = { 10, 10, 10, 10 };
    LabelInit.focused = false;

    LabelInit.caption = "Uref";
    pLTagUref = new TLinkedTagLabel("", "U1.RAM.Uref", LabelInit);
    pLTagUref->onEnterPressed = [this](int arg) { goToTagInfoPage(arg); };

    LabelInit.caption = "Iref";
    pLTagIref = new TLinkedTagLabel("", "U1.RAM.Iref", LabelInit);
    pLTagIref->onEnterPressed = [this](int arg) { goToTagInfoPage(arg); };

    LabelInit.caption = "UoutAve";
    pLTagUoutAve = new TLinkedTagLabel("", "U1.RAM.UoutAve", LabelInit);
    pLTagUoutAve->onEnterPressed = [this](int arg) { goToTagInfoPage(arg); };

    LabelInit.caption = "IoutAve";
    pLTagIoutAve = new TLinkedTagLabel("", "U1.RAM.IoutAve", LabelInit);
    pLTagIoutAve->onEnterPressed = [this](int arg) { goToTagInfoPage(arg); };

    LabelInit.caption = "SparkFrq";
    pLTagSparkFrq = new TLinkedTagLabel("", "U1.RAM.SparkFrq", LabelInit);
    pLTagSparkFrq->onEnterPressed = [this](int arg) { goToTagInfoPage(arg); };

    LabelInit.caption = "Out";
    pLTagOut = new TLinkedTagLabel("", "U1.RAM.Out", LabelInit);
    pLTagOut->onEnterPressed = [this](int arg) { goToTagInfoPage(arg); };

    LabelInit.caption = "IinAve";
    pLTagIinAve = new TLinkedTagLabel("", "U1.RAM.IinAve", LabelInit);
    pLTagIinAve->onEnterPressed = [this](int arg) { goToTagInfoPage(arg); };

    MainMenu = new TComponentListVertical({ pLTagUref    , pLTagIref     , pLTagUoutAve ,
                                            pLTagIoutAve , pLTagSparkFrq , pLTagOut ,
                                            pLTagIinAve });

    AddList({ MainMenu });
};

TPageHome::~TPageHome() {
};
