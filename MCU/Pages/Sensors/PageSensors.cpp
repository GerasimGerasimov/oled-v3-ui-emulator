#include "PageSensors.h"
#include "Router.h"
#include "TagLineScrollCaptionComment.h"
#include <IniResources.h>
#include <FixedHeader.h>

void TPageSensors::view() {
    Container->view();
};

void TPageSensors::onOpen() {
    fillPageContainer();
    SubscriberID = HandlerSubscribers::set("U1/RAM/", [this](TSlotHandlerArsg args) { SlotUpdate(args); });
}

void TPageSensors::startToClose() {
    HandlerSubscribers::remove("U1/RAM/", SubscriberID);
    TagList->Clear();
    isOpen = false;
}

bool TPageSensors::ProcessMessage(TMessage* m) {
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

TVisualObject* TPageSensors::getSignalOfFocusedChild() {
    for (auto& element : Container->List) {
        TVisualObject* e = element->getFocusedElement();
        TParameter* p = (e) ? (TParameter*) e->getDataSrc() : nullptr;
        if (p) return e;
    }
    return nullptr;
}

void TPageSensors::fillPageContainer(void) {
    TagList->Clear();
    TLabelInitStructure LabelInit;
    LabelInit.style = LabelsStyle::WIDTH_FIXED;
    LabelInit.Rect = { 10, 10, 10, 70 };
    LabelInit.focused = false;
    TagList->AddList({
        new TTagLineScrollCaptionComment("U1/RAM/Uin/", LabelInit),
        new TTagLineScrollCaptionComment("U1/RAM/Ua/", LabelInit),
        new TTagLineScrollCaptionComment("U1/RAM/Ub/", LabelInit),
        new TTagLineScrollCaptionComment("U1/RAM/Uc/", LabelInit),
        new TTagLineScrollCaptionComment("U1/RAM/Iin/", LabelInit),
        new TTagLineScrollCaptionComment("U1/RAM/Ia/", LabelInit),
        new TTagLineScrollCaptionComment("U1/RAM/Ib/", LabelInit),
        new TTagLineScrollCaptionComment("U1/RAM/Ic/", LabelInit),
        new TTagLineScrollCaptionComment("U1/RAM/UoutCur/", LabelInit),
        new TTagLineScrollCaptionComment("U1/RAM/IoutCur/", LabelInit),
        new TTagLineScrollCaptionComment("U1/RAM/Tradiator1/", LabelInit),
        new TTagLineScrollCaptionComment("U1/RAM/Tradiator2/", LabelInit),
        new TTagLineScrollCaptionComment("U1/RAM/Tcabinet/", LabelInit),
        new TTagLineScrollCaptionComment("U1/RAM/Alpha/", LabelInit),
        new TTagLineScrollCaptionComment("U1/RAM/Fin/", LabelInit),
        new TTagLineScrollCaptionComment("U1/RAM/Td_com/", LabelInit),
    });
}

TPageSensors::TPageSensors(std::string Name)
    :TPage(Name) {
    TVerticalContainerProps props = { false };
    Container = new TVerticalContainer(props, {});

    TLabelInitStructure LabelInit;
    LabelInit.pOwner = Container;
    LabelInit.caption = "Датчики";
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

void TPageSensors::SlotUpdate(TSlotHandlerArsg args) {
    for (auto& e : TagList->List) {
        TTagLine* tag = (TTagLine*)e;
        TParameter* p = (TParameter*)tag->getDataSrc();
        tag->Value->setCaption(p->getValue(args, ""));
    }
    Msg::send_message((u32)EventSrc::REPAINT, 0, 0);
}

TPageSensors::~TPageSensors() {
    TagList->Clear();
    Container->Clear();
    delete Container;
};
