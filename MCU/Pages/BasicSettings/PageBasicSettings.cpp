#include "PageBasicSettings.h"
#include "Router.h"
#include "TagLine.h"
#include "TagLineScrollCaptionComment.h"
#include <IniResources.h>
#include <FixedHeader.h>

void TPageBasicSettings::view() {
    Container->view();
};

void TPageBasicSettings::onOpen() {
    fillPageContainer();
    SubscriberID = HandlerSubscribers::set("U1/FLASH/", [this](TSlotHandlerArsg args) { SlotUpdate(args); });
}

void TPageBasicSettings::startToClose() {
    HandlerSubscribers::remove("U1/FLASH/", SubscriberID);
    TagList->Clear();
    isOpen = false;
}

bool TPageBasicSettings::ProcessMessage(TMessage* m) {
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

TVisualObject* TPageBasicSettings::getSignalOfFocusedChild() {
    for (auto& element : Container->List) {
        TVisualObject* e = element->getFocusedElement();
        TParameter* p = (e) ? (TParameter*) e->getDataSrc() : nullptr;
        if (p) return e;
    }
    return nullptr;
}

void TPageBasicSettings::fillPageContainer(void) {
    TagList->Clear();
    TLabelInitStructure LabelInit;
    LabelInit.style = LabelsStyle::WIDTH_FIXED;
    LabelInit.Rect = { 10, 10, 10, 65};
    LabelInit.focused = false;

    TagList->AddList({
        new TTagLine("Iovl", "U1/FLASH/Iovl/", LabelInit),
        new TTagLine("Uz", "U1/FLASH/Uz/", LabelInit),
        new TTagLine("UmaxSpRect", "U1/FLASH/UmaxSpRect/", LabelInit),
        new TTagLine("UminSpRect", "U1/FLASH/UminSpRect/", LabelInit),
        new TTagLine("FmaxSpRect", "U1/FLASH/FmaxSpRect/", LabelInit),
        new TTagLine("FminSpRect", "U1/FLASH/FminSpRect/", LabelInit),
        new TTagLine("SUPPLFltT", "U1/FLASH/SUPPLFltTime/", LabelInit),
        new TTagLine("RInslLow", "U1/FLASH/RInslLow/", LabelInit),
        new TTagLine("RInslFlt", "U1/FLASH/RInslFlt/", LabelInit),
        new TTagLine("RInslUp", "U1/FLASH/RInslUp/", LabelInit),
        new TTagLine("RInslFltEn", "U1/FLASH/RInslFltEnable/", LabelInit),
        new TTagLine("IrMaxFlt", "U1/FLASH/IrMaxFlt/", LabelInit),
        new TTagLine("IttMaxFlt", "U1/FLASH/IttMaxFlt/", LabelInit),
        new TTagLine("Ti", "U1/FLASH/Ti/", LabelInit),
        new TTagLine("Ku", "U1/FLASH/Ku/", LabelInit),
        new TTagLine("Td", "U1/FLASH/Td/", LabelInit),
        new TTagLine("Amax", "U1/FLASH/Amax/", LabelInit),
        new TTagLine("Amin", "U1/FLASH/Amin/", LabelInit),
        new TTagLine("UzLow", "U1/FLASH/UzLow/", LabelInit),
        new TTagLine("Ti2tR", "U1/FLASH/Ti2tR/", LabelInit),
        new TTagLine("i2tOV_ON", "U1/FLASH/i2tOV_ON_R/", LabelInit),
        new TTagLine("i2tOV_OFF", "U1/FLASH/i2tOV_OFF_R/", LabelInit),
        new TTagLine("IzI2tRLim", "U1/FLASH/Iz_i2t_R_limit/", LabelInit),
        new TTagLine("fUzMin", "U1/FLASH/fUzMin/", LabelInit),
        new TTagLine("fUzMax", "U1/FLASH/fUzMax/", LabelInit),
        new TTagLine("UzBias", "U1/FLASH/UzBias/", LabelInit),
        new TTagLine("fULoadMax", "U1/FLASH/fUloadMax/", LabelInit),
        new TTagLine("fULMaxTime", "U1/FLASH/fUloadMaxTime/", LabelInit),
    });
}

TPageBasicSettings::TPageBasicSettings(std::string Name)
    :TPage(Name) {
    TVerticalContainerProps props = { true };
    Container = new TVerticalContainer(props, {});

    TLabelInitStructure LabelInit;
    LabelInit.pOwner = Container;
    LabelInit.caption = "Основные уставки";
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

void TPageBasicSettings::SlotUpdate(TSlotHandlerArsg args) {
    for (auto& e : TagList->List) {
        TTagLine* tag = (TTagLine*)e;
        TParameter* p = (TParameter*)tag->getDataSrc();
        tag->Value->setCaption(p->getValue(args, ""));
    }
    Msg::send_message((u32)EventSrc::REPAINT, 0, 0);
}

TPageBasicSettings::~TPageBasicSettings() {
    TagList->Clear();
    Container->Clear();
    delete Container;
};
