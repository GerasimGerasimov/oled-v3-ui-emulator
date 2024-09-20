#include "PageBasicProtectionsSettings.h"
#include "Router.h"
#include "TagLine.h"
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
    LabelInit.style = LabelsStyle::WIDTH_DINAMIC;
    LabelInit.Rect = { 10, 10, 10, 10 };
    LabelInit.focused = false;
    TagList->AddList({
        //new TTagLine("UoutMax", "U1/FLASH/UoutMax/", LabelInit),
        //new TTagLine("tUOutMax", "U1/FLASH/tUOutMax/", LabelInit),
        //new TTagLine("FinMin", "U1/FLASH/FinMin/", LabelInit),
        //new TTagLine("FinMax", "U1/FLASH/FinMax/", LabelInit),
        //new TTagLine("dIinAsym", "U1/FLASH/dIinAsym/", LabelInit),
        //new TTagLine("tIinAsym", "U1/FLASH/tIinAsym/", LabelInit),
        //new TTagLine("dUasym", "U1/FLASH/dUasym/", LabelInit),
        //new TTagLine("tUinAsym", "U1/FLASH/tUinAsym/", LabelInit),
        //new TTagLine("UinMin", "U1/FLASH/UinMin/", LabelInit),
        //new TTagLine("UinMax", "U1/FLASH/UinMax/", LabelInit),
        //new TTagLine("tIinMTZ", "U1/FLASH/tIinMTZ/", LabelInit),
        //new TTagLine("IinMTZ", "U1/FLASH/IinMTZ/", LabelInit),
        //new TTagLine("tIoutMTZ", "U1/FLASH/tIoutMTZ/", LabelInit),
        //new TTagLine("IoutMTZ", "U1/FLASH/IoutMTZ/", LabelInit),
        //new TTagLine("tQ1", "U1/FLASH/tQ1/", LabelInit),
        //new TTagLine("tUInMax", "U1/FLASH/tUInMaxPhase/", LabelInit),
        //new TTagLine("tFinFail", "U1/FLASH/tFinFail/", LabelInit),
        //new TTagLine("tKM1", "U1/FLASH/tKM1/", LabelInit),
        //new TTagLine("tsyncfail", "U1/FLASH/tsyncfail/", LabelInit),
        //new TTagLine("tILongKM1", "U1/FLASH/tILongKM1/", LabelInit),
    });
}

TPageBasicProtectionsSettings::TPageBasicProtectionsSettings(std::string Name)
    :TPage(Name) {
    TVerticalContainerProps props = { false };
    Container = new TVerticalContainer(props, {});

    TLabelInitStructure LabelInit;
    LabelInit.pOwner = Container;
    LabelInit.caption = "Защиты. Основные";
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
