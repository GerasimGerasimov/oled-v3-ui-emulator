#include "PageHome.h"
#include "Router.h"
#include <IniResources.h>

void TPageHome::view() {
    MainMenu->view();
};

void TPageHome::onOpen() {
    SubscriberID = HandlerSubscribers::set("U1/RAM/", [this](TSlotHandlerArsg args) { SlotU1RAMUpdate(args); });
}

void TPageHome::startToClose() {
    HandlerSubscribers::remove("U1/RAM/", SubscriberID);
    isOpen = false;
}

bool TPageHome::ProcessMessage(TMessage* m) {
    TVisualObject* e = { nullptr };
    switch (m->Event) {
        case (u32)EventSrc::KEYBOARD: {
            switch (m->p1) {
                case (u32)KeyCodes::ESC:
                    TRouter::setTask({ false, "MainMenu", nullptr });
                    break;
                case (u32)KeyCodes::F1:
                    e = getSignalOfFocusedChild();
                    if (e) {
                        ISignal* p = IniResources::getSignalByTag(((TTagLine*)(e))->Tag);
                        TRouter::setTask({ false, "Help", p });
                    }
                    break;
                case (u32)KeyCodes::ENT:
                    e = getSignalOfFocusedChild();
                    if (e) {
                        TRouter::PageValueEditEntryData.tag = ((TTagLine*)(e))->Tag;
                        TRouter::PageValueEditEntryData.value = ((TTagLine*)(e))->Value->getCaption();
                        TRouter::setTask({ false, "EditValue", nullptr });
                    }
                    break;
            }
        }
    }

    for (auto& element : List) {
        element->ProcessMessage(m);
    }
    return false;
};

TVisualObject* TPageHome::getSignalOfFocusedChild() {
    for (auto& element : List) {
        TVisualObject* e = element->getFocusedElement();
        TParameter* p = (e) ? (TParameter*) e->getDataSrc() : nullptr;
        if (p) return e;
    }
    return nullptr;
}

void TPageHome::goToTagInfoPage(int a) {
    TRouter::setTask({ false, "Counters", nullptr });
}

TPageHome::TPageHome(std::string Name)
    :TPage(Name) {
    TVerticalContainerProps props = { false };
    TLabelInitStructure LabelInit;
    LabelInit.style = LabelsStyle::WIDTH_DINAMIC;
    LabelInit.Rect = { 10, 10, 10, 10 };
    LabelInit.focused = false;
/*TODO SignalFactoty если не находит параметра (BIT, WORD я об этом) то на МК приложение падает
проверить под WIN*/ 
    pLTagUref     = new TTagLine("Uref", "U1/RAM/Uref/", LabelInit);
    pLTagUref->inFocus = true;
    pLTagIref     = new TTagLine("Iref", "U1/RAM/Iref/", LabelInit);
    pLTagUoutAve  = new TTagLine("UoutAve", "U1/RAM/UoutAve/", LabelInit);
    pLTagIoutAve  = new TTagLine("IoutAve", "U1/RAM/IoutAve/", LabelInit);
    pLTagSparkFrq = new TTagLine("SpReq", "U1/RAM/SparkFrq/", LabelInit);
    pLTagOut      = new TTagLine("Out", "U1/RAM/Out/", LabelInit);

    MainMenu = new TVerticalContainer(props, { pLTagUref    , pLTagIref     , pLTagUoutAve,
                                            pLTagIoutAve , pLTagSparkFrq , pLTagOut});
    
    MainMenu->FocusedLine = 0;

    AddList({ MainMenu });
};

void TPageHome::SlotU1RAMUpdate(TSlotHandlerArsg args) {
    pLTagUref->Value->setCaption(((TParameter*)pLTagUref->getDataSrc())->getValue(args, ""));
    pLTagIref->Value->setCaption(((TParameter*)pLTagIref->getDataSrc())->getValue(args, ""));
    pLTagOut->Value->setCaption(((TParameter*)pLTagOut->getDataSrc())->getValue(args, ""));
    pLTagUoutAve->Value->setCaption(((TParameter*)pLTagUoutAve->getDataSrc())->getValue(args, ""));
    pLTagIoutAve->Value->setCaption(((TParameter*)pLTagIoutAve->getDataSrc())->getValue(args, ""));
    pLTagSparkFrq->Value->setCaption(((TParameter*)pLTagSparkFrq->getDataSrc())->getValue(args, ""));
    Msg::send_message((u32)EventSrc::REPAINT, 0, 0);
}

TPageHome::~TPageHome() {
};
