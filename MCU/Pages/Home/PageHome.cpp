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
                case (u32)KeyCodes::ESC:
                    TRouter::setActivePage("MainMenu", NULL); //TRouter::goBack();
                    return false;
                case (u32)KeyCodes::F1:
                    ISignal* p = getSignalOfFocusedChild();
                    TRouter::setActivePage("Help", p);
                    return false;
            }
        }
    }

    for (auto& element : List) {
        element->ProcessMessage(m);
    }
    return false;
};

/*TODO ���� �������� ������ ������� ������ � ��������� � ������*/
ISignal* TPageHome::getSignalOfFocusedChild() {
    for (auto& element : List) {
        std::vector<TVisualObject*> res = element->getFocusedElements();
        TVisualObject* e = (res.size() != 0) ? res[0] : NULL;

    }
    return NULL;
}

void TPageHome::goToTagInfoPage(int a) {
    TRouter::setActivePage("Counters", NULL);
}

TPageHome::TPageHome(std::string Name)
    :TPage(Name) {
    TLabelInitStructure LabelInit;
    LabelInit.style = LabelsStyle::LS_DINAMIC;
    LabelInit.Rect = { 10, 10, 10, 10 };
    LabelInit.focused = false;

    LabelInit.caption = "Fgen";
    pLTagUref = new TTagLine("U1/RAM/Fgen/", LabelInit);

    LabelInit.caption = "Phi";
    pLTagIref = new TTagLine("U1/RAM/Phi/", LabelInit);

    LabelInit.caption = "UbusOK";
    pLTagUoutAve = new TTagLine("U1/RAM/UbusOK/", LabelInit);

    LabelInit.caption = "DVA";  //"U1/CD/Modbus_Local1_DVA/"
    pLTagIoutAve = new TTagLine("U1/FLASH/Modbus_RS485_DVA/", LabelInit);

    LabelInit.caption = "Un";
    pLTagSparkFrq = new TTagLine("U1/FLASH/Unominal/", LabelInit);

    LabelInit.caption = "Ugen";
    pLTagOut = new TTagLine("U1/RAM/Ugen/", LabelInit);

    MainMenu = new TComponentListVertical({ pLTagUref    , pLTagIref     , pLTagUoutAve ,
                                            pLTagIoutAve , pLTagSparkFrq , pLTagOut /*,
                                            pLTagIinAve */ });

    AddList({ MainMenu });

    HandlerSubscribers::set("U1/RAM/", [this](TSlotHandlerArsg args) { SlotU1RAMUpdate(args); });
    HandlerSubscribers::set("U1/FLASH/", [this](TSlotHandlerArsg args) { SlotU1FLASHUpdate(args); });
    HandlerSubscribers::set("U1/CD/", [this](TSlotHandlerArsg args) { SlotU1CDUpdate(args); });
};

void TPageHome::SlotU1RAMUpdate(TSlotHandlerArsg args) {
    pLTagUref->Value->setCaption(pLTagUref->DataSrc->getValue(args, "%.2f"));
    pLTagIref->Value->setCaption(pLTagIref->DataSrc->getValue(args, "%.2f"));
    pLTagOut->Value->setCaption(pLTagOut->DataSrc->getValue(args, "%.2f"));
    pLTagUoutAve->Value->setCaption(pLTagUoutAve->DataSrc->getValue(args, ""));

    Msg::send_message(REPAINT, 0, 0);
}

void TPageHome::SlotU1FLASHUpdate(TSlotHandlerArsg args) {
    pLTagSparkFrq->Value->setCaption(pLTagSparkFrq->DataSrc->getValue(args, "%.0f"));
    pLTagIoutAve->Value->setCaption(pLTagIoutAve->DataSrc->getValue(args, "%.0f"));
    Msg::send_message(REPAINT, 0, 0);
}

void TPageHome::SlotU1CDUpdate(TSlotHandlerArsg args) {
    //pLTagIoutAve->Value->setCaption(pLTagIoutAve->DataSrc->getValue(args, "%.0f"));

    //Msg::send_message(REPAINT, 0, 0);
}


TPageHome::~TPageHome() {
};
