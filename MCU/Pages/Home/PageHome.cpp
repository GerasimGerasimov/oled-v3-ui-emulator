#include "PageHome.h"
#include "Router.h"
#include "TagLineScrollCaptionComment.h"
#include <IniResources.h>

void TPageHome::view() {
    TagList->view();
};

void TPageHome::onOpen() {
    fillPageContainer();
    SubscriberID = HandlerSubscribers::set("U1/RAM/", [this](TSlotHandlerArsg args) { SlotUpdate(args); });
}

void TPageHome::startToClose() {
    HandlerSubscribers::remove("U1/RAM/", SubscriberID);
    TagList->Clear();
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

TVisualObject* TPageHome::getSignalOfFocusedChild() {
    for (auto& element : List) {
        TVisualObject* e = element->getFocusedElement();
        TParameter* p = (e) ? (TParameter*) e->getDataSrc() : nullptr;
        if (p) return e;
    }
    return nullptr;
}

void TPageHome::fillPageContainer(void) {
    TagList->Clear();
    TLabelInitStructure LabelInit;
    LabelInit.style = LabelsStyle::WIDTH_FIXED;
    LabelInit.Rect = {10, 10, 10, 70};
    LabelInit.focused = false;
    TagList->AddList({
        new TTagLineScrollCaptionComment("U1/RAM/K3/", LabelInit),
        new TTagLineScrollCaptionComment("U1/RAM/K2/", LabelInit),
        new TTagLineScrollCaptionComment("U1/RAM/SA2/", LabelInit),
        new TTagLineScrollCaptionComment("U1/RAM/SA1/", LabelInit),
        new TTagLineScrollCaptionComment("U1/RAM/K1/", LabelInit),
        new TTagLineScrollCaptionComment("U1/RAM/KM1/", LabelInit),
        new TTagLineScrollCaptionComment("U1/RAM/K5/", LabelInit),
        new TTagLine("Øêàô ØÒ t", "U1/RAM/TWardrobe/", LabelInit),
        new TTagLine("Øêàô ØÑ t", "U1/RAM/TReststor/", LabelInit)
    });
    
}

TPageHome::TPageHome(std::string Name)
    :TPage(Name) {
    TVerticalContainerProps props = { false };
    TagList = new TVerticalContainer(props, {});
    AddList({ TagList });
};

void TPageHome::SlotUpdate(TSlotHandlerArsg args) {
    for (auto& e : TagList->List) {
        e->update(args, "");
    }
    Msg::send_message((u32)EventSrc::REPAINT, 0, 0);
}

TPageHome::~TPageHome() {
    TagList->Clear();
    delete TagList;
};
