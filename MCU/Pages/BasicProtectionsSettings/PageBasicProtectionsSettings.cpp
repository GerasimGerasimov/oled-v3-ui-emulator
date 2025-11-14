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
    LabelInit.style = LabelsStyle::WIDTH_FIXED;
    LabelInit.Rect = { 10, 10, 10, 80 };
    LabelInit.focused = false;
    TagList->AddList({
        new TTagLine("IinMTZ", "U1/FLASH/IinMTZ/", LabelInit),
        new TTagLine("IoutMTZ", "U1/FLASH/IoutMTZ/", LabelInit),
        new TTagLine("IovrSt1", "U1/FLASH/IovrSt1/", LabelInit),
        new TTagLine("IovrSt2", "U1/FLASH/IovrSt2/", LabelInit),
        new TTagLine("IovrSt3", "U1/FLASH/IovrSt3/", LabelInit),
        new TTagLine("IovrSt4", "U1/FLASH/IovrSt4/", LabelInit),
        new TTagLine("dIasym", "U1/FLASH/dIasym/", LabelInit),
        new TTagLine("dUasym", "U1/FLASH/dUasym/", LabelInit),
        new TTagLine("UinMin", "U1/FLASH/UinMin/", LabelInit),
        new TTagLine("UinMax", "U1/FLASH/UinMax/", LabelInit),
        new TTagLine("FinMin", "U1/FLASH/FinMin/", LabelInit),
        new TTagLine("FinMax", "U1/FLASH/FinMax/", LabelInit),
        new TTagLine("UoutMin", "U1/FLASH/UoutMin/", LabelInit),
        new TTagLine("UoutMax", "U1/FLASH/UoutMax/", LabelInit),
        new TTagLine("ContBallIgnore", "U1/FLASH/ContBallIgnore/", LabelInit),
        new TTagLine("Tfan1On", "U1/FLASH/Tfan1On/", LabelInit),
        new TTagLine("Tfan1Off", "U1/FLASH/Tfan1Off/", LabelInit),
        new TTagLine("Tovr", "U1/FLASH/Tovr/", LabelInit),
        new TTagLine("Tfan2On", "U1/FLASH/Tfan2On/", LabelInit),
        new TTagLine("Tfan2Off", "U1/FLASH/Tfan2Off/", LabelInit),
    });
}

TPageBasicProtectionsSettings::TPageBasicProtectionsSettings(std::string Name)
    :TPage(Name) {
    TVerticalContainerProps props = { false };
    Container = new TVerticalContainer(props, {});

    TLabelInitStructure LabelInit;
    LabelInit.pOwner = Container;
    LabelInit.caption = "Уставки защит";
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
