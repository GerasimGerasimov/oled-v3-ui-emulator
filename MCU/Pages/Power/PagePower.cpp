#include "PagePower.h"
#include "TagLineScrollCaptionComment.h"
#include "Router.h"
#include "TagLine.h"
#include <IniResources.h>
#include <FixedHeader.h>

void TPagePower::view() {
    Container->view();
};

void TPagePower::onOpen() {
    fillPageContainer();
    SubscriberID = HandlerSubscribers::set("U1/RAM/", [this](TSlotHandlerArsg args) { SlotUpdate(args); });
}

void TPagePower::startToClose() {
    HandlerSubscribers::remove("U1/RAM/", SubscriberID);
    TagList->Clear();
    isOpen = false;
}
TPagePower::TPagePower(std::string Name)
    :TPage(Name) {
    TVerticalContainerProps props = { false };
    Container = new TVerticalContainer(props, {});

    TLabelInitStructure LabelInit;
    LabelInit.pOwner = Container;
    LabelInit.caption = "Мощность";
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

void TPagePower::fillPageContainer(void){
    TagList->Clear();
    TLabelInitStructure LabelInit;
    LabelInit.style = LabelsStyle::WIDTH_FIXED;
    LabelInit.Rect = {10, 10, 10, 80};
    LabelInit.focused = false;

    TagList->AddList({
        new TTagLineScrollCaptionComment("U1/RAM/Ssg/", LabelInit),
        new TTagLineScrollCaptionComment("U1/RAM/Psg/", LabelInit),
        new TTagLineScrollCaptionComment("U1/RAM/Qsg/", LabelInit),
        new TTagLineScrollCaptionComment("U1/RAM/Qoe/", LabelInit),
        new TTagLineScrollCaptionComment("U1/RAM/QLimMin/", LabelInit),
        new TTagLineScrollCaptionComment("U1/RAM/QLimMax/", LabelInit),
        });
}

bool TPagePower::ProcessMessage(TMessage* m) {
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
            return true;

        }
    }
    }

    for (auto& element : List) {
        element->ProcessMessage(m);
    }
    return false;
};

TVisualObject* TPagePower::getSignalOfFocusedChild() {
    for (auto& element : Container->List) {
        TVisualObject* e = element->getFocusedElement();
        TParameter* p = (e) ? (TParameter*)e->getDataSrc() : nullptr;
        if (p) return e;
    }
    return nullptr;
}


void TPagePower::SlotUpdate(TSlotHandlerArsg args) {
    for (auto& e : TagList->List) {
        TTagLine* tag = (TTagLine*)e;
        TParameter* p = (TParameter*)tag->getDataSrc();
        tag->Value->setCaption(p->getValue(args, ""));
    }
    Msg::send_message((u32)EventSrc::REPAINT, 0, 0);
}

TPagePower::~TPagePower() {
    TagList->Clear();
    Container->Clear();
    delete Container;
};
