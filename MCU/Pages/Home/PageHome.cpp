#include "PageHome.h"
#include "Router.h"

void TPageHome::view() {
    MainMenu->view();
};

void TPageHome::clear() {
}

bool TPageHome::ProcessMessage(TMessage* m) {
    TSignalOnFocus SoF = { NULL, NULL };
    switch (m->Event) {
        case (u32)EventSrc::KEYBOARD: {
            switch (m->p1) {
                case (u32)KeyCodes::ESC:
                    TRouter::setTask({ false, "MainMenu", NULL });
                    break;
                case (u32)KeyCodes::F1:
                    SoF = getSignalOfFocusedChild();
                    if (SoF.signal) {
                        TRouter::setTask({ false, "Help", SoF.signal });
                    }
                    break;
                case (u32)KeyCodes::ENT:
                    SoF = getSignalOfFocusedChild();
                    if (SoF.signal) {
                        /*TODO насыщать страницу EditValue*/
                        TRouter::PageValueEditEntryData.signal = SoF.signal;
                        TRouter::PageValueEditEntryData.value = ((TTagLine*)(SoF.element))->Value->getCaption();
                        TRouter::setTask({ false, "EditValue", NULL });
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

TSignalOnFocus TPageHome::getSignalOfFocusedChild() {
    for (auto& element : List) {
        TVisualObject* e = element->getFocusedElement();
        TParameter* p = (e) ? (TParameter*) e->getDataSrc() : NULL;
        if (p) return { p , e };
    }
    return { NULL, NULL };
}

void TPageHome::goToTagInfoPage(int a) {
    TRouter::setTask({ false, "Counters", NULL });
}

TPageHome::TPageHome(std::string Name)
    :TPage(Name) {
    TLabelInitStructure LabelInit;
    LabelInit.style = LabelsStyle::WIDTH_DINAMIC;
    LabelInit.Rect = { 10, 10, 10, 10 };
    LabelInit.focused = false;

    pLTagUref     = new TTagLine("Fgen", "U1/RAM/Fgen/", LabelInit);
    pLTagUref->inFocus = true;
    pLTagIref     = new TTagLine("Phi", "U1/RAM/Phi/", LabelInit);
    pLTagUoutAve  = new TTagLine("UbusOK", "U1/RAM/UbusOK/", LabelInit);
    pLTagIoutAve  = new TTagLine("DVA", "U1/FLASH/Modbus_RS485_DVA/", LabelInit);
    pLTagSparkFrq = new TTagLine("Un", "U1/FLASH/Unominal/", LabelInit);
    pLTagOut      = new TTagLine("Ugen", "U1/RAM/Ugen/", LabelInit);

    MainMenu = new TComponentListVertical({ pLTagUref    , pLTagIref     , pLTagUoutAve ,
                                            pLTagIoutAve , pLTagSparkFrq , pLTagOut /*,
                                            pLTagIinAve */ });
    
    MainMenu->FocusedLine = 0;

    AddList({ MainMenu });

    HandlerSubscribers::set("U1/RAM/",   [this](TSlotHandlerArsg args) { SlotU1RAMUpdate(args); });
    HandlerSubscribers::set("U1/FLASH/", [this](TSlotHandlerArsg args) { SlotU1FLASHUpdate(args); });
    HandlerSubscribers::set("U1/CD/",    [this](TSlotHandlerArsg args) { SlotU1CDUpdate(args); });
};

//        //((TParameter*)DataSrc)
void TPageHome::SlotU1RAMUpdate(TSlotHandlerArsg args) {
    pLTagUref->Value->setCaption(((TParameter*)pLTagUref->getDataSrc())->getValue(args, "%.2f"));
    pLTagIref->Value->setCaption(((TParameter*)pLTagIref->getDataSrc())->getValue(args, "%.2f"));
    pLTagOut->Value->setCaption(((TParameter*)pLTagOut->getDataSrc())->getValue(args, "%.2f"));
    pLTagUoutAve->Value->setCaption(((TParameter*)pLTagUoutAve->getDataSrc())->getValue(args, ""));

    Msg::send_message((u32)EventSrc::REPAINT, 0, 0);
}

void TPageHome::SlotU1FLASHUpdate(TSlotHandlerArsg args) {
    pLTagSparkFrq->Value->setCaption(((TParameter*)pLTagSparkFrq->getDataSrc())->getValue(args, "%.0f"));
    pLTagIoutAve->Value->setCaption(((TParameter*)pLTagIoutAve->getDataSrc())->getValue(args, "%.0f"));
    Msg::send_message((u32)EventSrc::REPAINT, 0, 0);
}

void TPageHome::SlotU1CDUpdate(TSlotHandlerArsg args) {
    //pLTagIoutAve->Value->setCaption(pLTagIoutAve->DataSrc->getValue(args, "%.0f"));

    //Msg::send_message(REPAINT, 0, 0);
}


TPageHome::~TPageHome() {
};
