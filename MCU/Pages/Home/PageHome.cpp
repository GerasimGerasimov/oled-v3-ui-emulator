#include "PageHome.h"
#include "Router.h"
#include "HandleSubscribers.h"

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
    pLTagUref = new TTagLine("U1/RAM/Ustat/", LabelInit);

    LabelInit.caption = "Istat";
    pLTagIref = new TTagLine("U1/RAM/Istat/", LabelInit);

    LabelInit.caption = "PWR.OK";
    pLTagUoutAve = new TTagLine("U1/RAM/DExS_PWR_OK/", LabelInit);

    LabelInit.caption = "DVA";
    pLTagIoutAve = new TTagLine("U1/CD/Modbus_Local1_DVA/", LabelInit);

    LabelInit.caption = "IstStart";
    pLTagSparkFrq = new TTagLine("U1/FLASH/IstStart/", LabelInit);

    MainMenu = new TComponentListVertical({ pLTagUref    , pLTagIref     , pLTagUoutAve ,
                                            pLTagIoutAve , pLTagSparkFrq /*, pLTagOut ,
                                            pLTagIinAve */ });

    AddList({ MainMenu });

    HandlerSubscribers::set("U1/RAM/", [this](bool valid) { SlotDataUpdate(valid); });
};

void TPageHome::SlotDataUpdate(bool valid) {

}

TPageHome::~TPageHome() {
};
