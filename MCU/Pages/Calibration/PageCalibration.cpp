#include "PageCalibration.h"
#include "Router.h"
#include "TagLine.h"
#include <IniResources.h>
#include <FixedHeader.h>

void TPageCalibration::view() {
    Container->view();
};

void TPageCalibration::onOpen() {
    fillPageContainer();
    SubscriberID = HandlerSubscribers::set("U1/CD/", [this](TSlotHandlerArsg args) { SlotUpdate(args); });
}

void TPageCalibration::startToClose() {
    HandlerSubscribers::remove("U1/CD/", SubscriberID);
    TagList->Clear();
    isOpen = false;
}

bool TPageCalibration::ProcessMessage(TMessage* m) {
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
                        TRouter::PageValueEditEntryData.backPage = Name;
                        TRouter::setTask({ false, "Help", p });
                    }
                    break;
                case (u32)KeyCodes::ENT:
                    e = getSignalOfFocusedChild();
                    if (e) {
                        TRouter::PageValueEditEntryData.tag = ((TTagLine*)(e))->Tag;
                        TRouter::PageValueEditEntryData.value = ((TTagLine*)(e))->Value->getCaption();
                        TRouter::PageValueEditEntryData.backPage = Name;
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

TVisualObject* TPageCalibration::getSignalOfFocusedChild() {
    for (auto& element : Container->List) {
        TVisualObject* e = element->getFocusedElement();
        TParameter* p = (e) ? (TParameter*) e->getDataSrc() : nullptr;
        if (p) return e;
    }
    return nullptr;
}

void TPageCalibration::fillPageContainer(void) {
    TagList->Clear();
    TLabelInitStructure LabelInit;
    LabelInit.style = LabelsStyle::WIDTH_DINAMIC;
    LabelInit.Rect = { 10, 10, 10, 10 };
    LabelInit.focused = false;
    TagList->AddList({
        new TTagLine("S_UtgToSpeed", "U1/CD/S_UtgToSpeed/", LabelInit),
        new TTagLine("S_UrefToSpdRef", "U1/CD/S_UrefToSpdRef/", LabelInit),
        new TTagLine("pK_Udcl", "U1/CD/pK_Udcl/", LabelInit),
        new TTagLine("pK_Idcl", "U1/CD/pK_Idcl/", LabelInit),
        new TTagLine("K_Ilin1", "U1/CD/K_Ilin1/", LabelInit),
        new TTagLine("K_Ilin2", "U1/CD/K_Ilin2/", LabelInit),
        new TTagLine("K_Ilin3", "U1/CD/K_Ilin3/", LabelInit),
        new TTagLine("pK_Utg", "U1/CD/pK_Utg/", LabelInit),
        new TTagLine("pK_Uref", "U1/CD/pK_Uref/", LabelInit),
        new TTagLine("pK_Uexc", "U1/CD/pK_Uexc/", LabelInit),
        new TTagLine("pK_Iexc", "U1/CD/pK_Iexc/", LabelInit),
        new TTagLine("mK_Udcl", "U1/CD/mK_Udcl/", LabelInit),
        new TTagLine("mK_Idcl", "U1/CD/mK_Idcl/", LabelInit),
        new TTagLine("mK_Utg", "U1/CD/mK_Utg/", LabelInit),
        new TTagLine("mK_Uref", "U1/CD/mK_Uref/", LabelInit),
        new TTagLine("mK_Uexc", "U1/CD/mK_Uexc/", LabelInit),
        new TTagLine("mK_Iexc", "U1/CD/mK_Iexc/", LabelInit),
        new TTagLine("S_DExS_PWR_R", "U1/CD/S_DExS_PWR_R/", LabelInit),
        new TTagLine("S_DExS_PWR_F", "U1/CD/S_DExS_PWR_F/", LabelInit),
        new TTagLine("S_DExS_PWR_U", "U1/CD/S_DExS_PWR_U/", LabelInit),
        new TTagLine("NoCurDelay", "U1/CD/NoCurDelay/", LabelInit),
        new TTagLine("MB_opt_DVA", "U1/CD/Modbus_option_DVA/", LabelInit),
        new TTagLine("MB_opt_BPS", "U1/CD/Modbus_option_BPS/", LabelInit),
        new TTagLine("S_UrefToUdcl", "U1/CD/S_UrefToUdcl/", LabelInit),
        new TTagLine("KTC", "U1/CD/KTC/", LabelInit),
        new TTagLine("TEngNom", "U1/CD/TEngNom/", LabelInit),
        new TTagLine("Y1_Tmin", "U1/CD/Y1_Tmin/", LabelInit),
        new TTagLine("X1_Tmin", "U1/CD/X1_Tmin/", LabelInit),
        new TTagLine("Y2_Tmax", "U1/CD/Y2_Tmax/", LabelInit),
        new TTagLine("X2_Tmax", "U1/CD/X2_Tmax/", LabelInit),

    });
}

TPageCalibration::TPageCalibration(std::string Name)
    :TPage(Name) {
    TVerticalContainerProps props = { false };
    Container = new TVerticalContainer(props, {});

    TLabelInitStructure LabelInit;
    LabelInit.pOwner = Container;
    LabelInit.caption = "Калибровки";
    TFixedHeader* pHeader = new TFixedHeader(LabelInit);
    Container->Add(pHeader);

    props = { true };
    TagList = new TVerticalContainer(props, {});
    TagList->ElementRect = { 0, 0,
                            (u16)(VIEW_PORT_MAX_HEIGHT - pHeader->getHeight() - 1),
                            VIEW_PORT_MAX_WIDTH };
    Container->Add(TagList);

    AddList({ Container });
};

void TPageCalibration::SlotUpdate(TSlotHandlerArsg args) {
    for (auto& e : TagList->List) {
        TTagLine* tag = (TTagLine*)e;
        TParameter* p = (TParameter*)tag->getDataSrc();
        tag->Value->setCaption(p->getValue(args, ""));
    }
    Msg::send_message((u32)EventSrc::REPAINT, 0, 0);
}

TPageCalibration::~TPageCalibration() {
    TagList->Clear();
    Container->Clear();
    delete Container;
};
