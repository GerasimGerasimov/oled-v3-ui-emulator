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

    LabelInit.caption = "Ustat";
    pLTagUref = new TLinkedTagLabel("U1/RAM/Ustat/", LabelInit);
    pLTagUref->onEnterPressed = [this](int arg) { goToTagInfoPage(arg); };

    LabelInit.caption = "Istat";
    pLTagIref = new TLinkedTagLabel("U1/RAM/Istat/", LabelInit);
    pLTagIref->onEnterPressed = [this](int arg) { goToTagInfoPage(arg); };

    LabelInit.caption = "DExS_PWR_OK";
    pLTagUoutAve = new TLinkedTagLabel("U1/RAM/DExS_PWR_OK/", LabelInit);
    pLTagUoutAve->onEnterPressed = [this](int arg) { goToTagInfoPage(arg); };

    LabelInit.caption = "SN";
    pLTagIoutAve = new TLinkedTagLabel("U1/CD/SN/", LabelInit);
    pLTagIoutAve->onEnterPressed = [this](int arg) { goToTagInfoPage(arg); };

    LabelInit.caption = "IstStart";
    pLTagSparkFrq = new TLinkedTagLabel("U1/FLASH/IstStart/", LabelInit);
    pLTagSparkFrq->onEnterPressed = [this](int arg) { goToTagInfoPage(arg); };

    MainMenu = new TComponentListVertical({ pLTagUref    , pLTagIref     , pLTagUoutAve ,
                                            pLTagIoutAve , pLTagSparkFrq /*, pLTagOut ,
                                            pLTagIinAve */ });

    AddList({ MainMenu });
};

TPageHome::~TPageHome() {
};
