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
        new TTagLineScrollCaptionComment("U1/FLASH/IchargeMin/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/IchargeMax/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/UchargeMax/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/UAddCharge/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/IAddCharge/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/tAddCharge/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/IEqualChargeMin/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/IEqualChargeMax/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/UEqualChargeMax/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/UEqualAddCharge/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/UEqualCharge/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/IEqualAddCharge/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/tEqualAddCharge/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/tEqualCharge/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/UdischargeMin/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/IdischargeMin/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/BatteryCapacity/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/tSoftStart/", LabelInit),
        new TTagLine("kRegU", "U1/FLASH/kRegU/", LabelInit),
        new TTagLine("kRegI", "U1/FLASH/kRegI/", LabelInit),
        new TTagLine("TiReg", "U1/FLASH/TiReg/", LabelInit),
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
