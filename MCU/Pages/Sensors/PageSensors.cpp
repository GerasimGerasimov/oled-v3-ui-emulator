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
        new TTagLine("TimeSec", "U1/RAM/TimeSec/", LabelInit),
        new TTagLine("Alpha", "U1/RAM/Alpha/", LabelInit),
        new TTagLine("WRun", "U1/RAM/WRun/", LabelInit),
        new TTagLine("i2tSum", "U1/RAM/i2tSum/", LabelInit),
        new TTagLine("Uout", "U1/RAM/Uout/", LabelInit),
        new TTagLine("Iout", "U1/RAM/Iout/", LabelInit),
        new TTagLine("Iin", "U1/RAM/Iin/", LabelInit),
        new TTagLine("Uin", "U1/RAM/Uin/", LabelInit),
        new TTagLine("Fin", "U1/RAM/Fin/", LabelInit),
        new TTagLine("Ia", "U1/RAM/Ia/", LabelInit),
        new TTagLine("Ib", "U1/RAM/Ib/", LabelInit),
        new TTagLine("Ic", "U1/RAM/Ic/", LabelInit),
        new TTagLine("Uab", "U1/RAM/Uab/", LabelInit),
        new TTagLine("Ubc", "U1/RAM/Ubc/", LabelInit),
        new TTagLine("Uca", "U1/RAM/Uca/", LabelInit)
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
