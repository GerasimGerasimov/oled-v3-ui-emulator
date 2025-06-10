#include "PageLimiters.h"
#include "Router.h"
#include "TagLine.h"
#include "TagLineScrollCaptionComment.h"
#include <IniResources.h>
#include <FixedHeader.h>

void TPageLimiters::view() {
    Container->view();
};

void TPageLimiters::onOpen() {
    fillPageContainer();
    SubscriberID = HandlerSubscribers::set("U1/FLASH/", [this](TSlotHandlerArsg args) { SlotUpdate(args); });
}

void TPageLimiters::startToClose() {
    HandlerSubscribers::remove("U1/FLASH/", SubscriberID);
    TagList->Clear();
    isOpen = false;
}

bool TPageLimiters::ProcessMessage(TMessage* m) {
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

TVisualObject* TPageLimiters::getSignalOfFocusedChild() {
    for (auto& element : Container->List) {
        TVisualObject* e = element->getFocusedElement();
        TParameter* p = (e) ? (TParameter*)e->getDataSrc() : nullptr;
        if (p) return e;
    }
    return nullptr;
}
void TPageLimiters::fillPageContainer(void) {
    TagList->Clear();
    TLabelInitStructure LabelInit;
    LabelInit.style = LabelsStyle::WIDTH_FIXED;
    LabelInit.Rect = { 10, 10, 10, 70 };
    LabelInit.focused = false;

    TagList->AddList({
        new TTagLine("fIzMin", "U1/FLASH/fIzMin/", LabelInit),
        new TTagLine("fIzMax", "U1/FLASH/fIzMax/", LabelInit),
        new TTagLine("Ti2tR", "U1/FLASH/Ti2tR/", LabelInit),
        new TTagLine("i2tOV_ON", "U1/FLASH/i2tOV_ON_R/", LabelInit),
        new TTagLine("i2tOV_OFF", "U1/FLASH/i2tOV_OFF_R/", LabelInit),
        new TTagLine("Iz_i2t_R_lim", "U1/FLASH/Iz_i2t_R_limit/", LabelInit),
        new TTagLine("Amax", "U1/FLASH/Amax/", LabelInit),
        new TTagLine("Amin", "U1/FLASH/Amin/", LabelInit),
        });
}

TPageLimiters::TPageLimiters(std::string Name) :TPage(Name) {
    TVerticalContainerProps props = { true };
    Container = new TVerticalContainer(props, {});

    TLabelInitStructure LabelInit;
    LabelInit.pOwner = Container;
    LabelInit.caption = "Ограничители";
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

void TPageLimiters::SlotUpdate(TSlotHandlerArsg args) {
    for (auto& e : TagList->List) {
        TTagLine* tag = (TTagLine*)e;
        TParameter* p = (TParameter*)tag->getDataSrc();
        tag->Value->setCaption(p->getValue(args, ""));
    }
    Msg::send_message((u32)EventSrc::REPAINT, 0, 0);
}

TPageLimiters::~TPageLimiters() {
    TagList->Clear();
    Container->Clear();
    delete Container;
};