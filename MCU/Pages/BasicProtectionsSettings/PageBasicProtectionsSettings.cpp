#include "PageBasicProtectionsSettings.h"
#include "Router.h"
#include "TagLineScrollCaptionComment.h"
#include <IniResources.h>
#include <FixedHeader.h>

void TPageBasicProtectionsSettings::view() {
    Container->view();
};

void TPageBasicProtectionsSettings::onOpen() {
    fillPageContainer();
    SubscriberID = HandlerSubscribers::set("U1/FLASH/", [this](TSlotHandlerArsg args) { SlotUpdate(args); });
}

void TPageBasicProtectionsSettings::startToClose() {
    HandlerSubscribers::remove("U1/FLASH/", SubscriberID);
    TagList->Clear();
    isOpen = false;
}

bool TPageBasicProtectionsSettings::ProcessMessage(TMessage* m) {
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

TVisualObject* TPageBasicProtectionsSettings::getSignalOfFocusedChild() {
    for (auto& element : Container->List) {
        TVisualObject* e = element->getFocusedElement();
        TParameter* p = (e) ? (TParameter*) e->getDataSrc() : nullptr;
        if (p) return e;
    }
    return nullptr;
}

void TPageBasicProtectionsSettings::fillPageContainer(void) {
    TagList->Clear();
    TLabelInitStructure LabelInit;
    LabelInit.style = LabelsStyle::WIDTH_FIXED;
    LabelInit.Rect = { 10, 10, 10, 70 };
    LabelInit.focused = false;
    TagList->AddList({
        new TTagLineScrollCaptionComment("U1/FLASH/IinMTZ/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/IoutMTZ/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/IovrSt1/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/IovrSt2/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/IovrSt3/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/IovrSt4/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/tOvrSt1/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/tOvrSt2/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/tOvrSt3/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/tOvrSt4/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/dIasym/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/dUasym/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/tAsym/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/UinMin/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/UinMax/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/FinMin/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/FinMax/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/UoutMin/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/tOutMin/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/UoutMax/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/tOutMax/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/tStartMax/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/Tovr/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/Tfan2On/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/Tfan2Off/", LabelInit),
    });
}

TPageBasicProtectionsSettings::TPageBasicProtectionsSettings(std::string Name)
    :TPage(Name) {
    TVerticalContainerProps props = { false };
    Container = new TVerticalContainer(props, {});

    TLabelInitStructure LabelInit;
    LabelInit.pOwner = Container;
    LabelInit.caption = "Защиты";
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

void TPageBasicProtectionsSettings::SlotUpdate(TSlotHandlerArsg args) {
    for (auto& e : TagList->List) {
        TTagLine* tag = (TTagLine*)e;
        TParameter* p = (TParameter*)tag->getDataSrc();
        tag->Value->setCaption(p->getValue(args, ""));
    }
    Msg::send_message((u32)EventSrc::REPAINT, 0, 0);
}

TPageBasicProtectionsSettings::~TPageBasicProtectionsSettings() {
    TagList->Clear();
    Container->Clear();
    delete Container;
};
