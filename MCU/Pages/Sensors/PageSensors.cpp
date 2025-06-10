#include "PageSensors.h"
#include "Router.h"
#include "TagLine.h"
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
    LabelInit.style = LabelsStyle::WIDTH_DINAMIC;
    LabelInit.Rect = { 10, 10, 10, 10 };
    LabelInit.focused = false;
    TagList->AddList({
        new TTagLine("PWR_OK", "U1/RAM/DExS_PWR_OK/", LabelInit),
        new TTagLine("FORCE", "U1/RAM/FORCE/", LabelInit),
        new TTagLine("INSL_LOW", "U1/RAM/R_INSL_LOW/", LabelInit),
        new TTagLine("INSL_FLT", "U1/RAM/R_INSL_FLT/", LabelInit),
        new TTagLine("PWR", "U1/RAM/PWR/", LabelInit),
        new TTagLine("PWR_LNK", "U1/RAM/DExS_PWR_LNK/", LabelInit),
        new TTagLine("FAULT", "U1/RAM/FAULT/", LabelInit),
        new TTagLine("T1000Hz", "U1/RAM/T1000Hz/", LabelInit),
        new TTagLine("i2tR", "U1/RAM/i2tR/", LabelInit),
        new TTagLine("uzr_min", "U1/RAM/uzr_min/", LabelInit),
        new TTagLine("uzr_max", "U1/RAM/uzr_max/", LabelInit),
        new TTagLine("IrMaxFlt", "U1/RAM/IrMaxFlt/", LabelInit),
        new TTagLine("IttMaxFlt", "U1/RAM/IttMaxFlt/", LabelInit),
        new TTagLine("UloadMaxFlt", "U1/RAM/UloadMaxFlt/", LabelInit),
    });
}

TPageSensors::TPageSensors(std::string Name)
    :TPage(Name) {
    TVerticalContainerProps props = { false };
    Container = new TVerticalContainer(props, {});

    TLabelInitStructure LabelInit;
    LabelInit.pOwner = Container;
    LabelInit.caption = "Индикаторы";
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
