#include "PageAutoMode.h"
#include "Router.h"
#include "TagLineScrollCaptionComment.h"
#include <IniResources.h>
#include <FixedHeader.h>
#include "parser.h"

void TPageAutoMode::view() {
    Container->view();
};

void TPageAutoMode::onOpen() {
    fillPageContainer();
    SubscriberIDFLASH = HandlerSubscribers::set("U1/FLASH/", [this](TSlotHandlerArsg args) { SlotUpdateFLASH(args); });
    SubscriberIDRAM = HandlerSubscribers::set("U1/RAM/", [this](TSlotHandlerArsg args) { SlotUpdateRAM(args); });
    SubscriberIDCD = HandlerSubscribers::set("U1/CD/", [this](TSlotHandlerArsg args) { SlotUpdateCD(args); });
}

void TPageAutoMode::startToClose() {
    HandlerSubscribers::remove("U1/FLASH/", SubscriberIDFLASH);
    HandlerSubscribers::remove("U1/RAM/", SubscriberIDRAM);
    HandlerSubscribers::remove("U1/CD/", SubscriberIDCD);
    TagList->Clear();
    isOpen = false;
}

bool TPageAutoMode::ProcessMessage(TMessage* m) {
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
                std::string EditPage = TRouter::selectEditPage(TRouter::PageValueEditEntryData.tag);
                TRouter::setTask({ false, EditPage, nullptr });
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

TVisualObject* TPageAutoMode::getSignalOfFocusedChild() {
    for (auto& element : Container->List) {
        TVisualObject* e = element->getFocusedElement();
        TParameter* p = (e) ? (TParameter*)e->getDataSrc() : nullptr;
        if (p) return e;
    }
    return nullptr;
}

void TPageAutoMode::fillPageContainer(void) {
    TagList->Clear();
    TLabelInitStructure LabelInit;
    LabelInit.style = LabelsStyle::WIDTH_FIXED;
    LabelInit.Rect = { 10, 10, 10, 80 };
    LabelInit.focused = false;
    TagList->AddList({
        new TTagLineScrollCaptionComment("U1/FLASH/AutoMode/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/WaitStable/", LabelInit),
        new TTagLineScrollCaptionComment("U1/CD/CFI_OFFSET/", LabelInit),
        new TTagLineScrollCaptionComment("U1/RAM/F/", LabelInit),
        new TTagLineScrollCaptionComment("U1/RAM/cfi_enable/", LabelInit),
        new TTagLineScrollCaptionComment("U1/RAM/cfu_enable/", LabelInit),
        new TTagLineScrollCaptionComment("U1/RAM/ExtRegTimeOut/", LabelInit),
        });
}

TPageAutoMode::TPageAutoMode(std::string Name)
    :TPage(Name) {
    TVerticalContainerProps props = { false };
    Container = new TVerticalContainer(props, {});

    TLabelInitStructure LabelInit;
    LabelInit.pOwner = Container;
    LabelInit.caption = "Автомат. режим";
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

void TPageAutoMode::SlotUpdateFLASH(TSlotHandlerArsg args) {
    SlotUpdate("/FLASH", args);
}

void TPageAutoMode::SlotUpdateRAM(TSlotHandlerArsg args) {
    SlotUpdate("/RAM", args);
}

void TPageAutoMode::SlotUpdateCD(TSlotHandlerArsg args) {
    SlotUpdate("/CD", args);
}

void TPageAutoMode::SlotUpdate(const char* sector, TSlotHandlerArsg args) {
    for (auto& e : TagList->List) {
        TTagLine* tag = (TTagLine*)e;
        if ((tag->Tag.find(sector)) != std::string::npos) {
            TParameter* p = (TParameter*)tag->getDataSrc();
            tag->Value->setCaption(p->getValue(args, ""));
        }
    }
    Msg::send_message((u32)EventSrc::REPAINT, 0, 0);
}

TPageAutoMode::~TPageAutoMode() {
    TagList->Clear();
    Container->Clear();
    delete Container;
};
