#include "PageControlSettings.h"
#include "Router.h"
#include "TagLineScrollCaptionComment.h"
#include <IniResources.h>
#include <FixedHeader.h>
#include "parser.h"

void TPageControlSettings::view() {
    Container->view();
};

void TPageControlSettings::onOpen() {
    fillPageContainer();
    SubscriberIDFLASH = HandlerSubscribers::set("U1/FLASH/", [this](TSlotHandlerArsg args) { SlotUpdateFLASH(args); });
    SubscriberIDRAM = HandlerSubscribers::set("U1/RAM/", [this](TSlotHandlerArsg args){ SlotUpdateRAM(args); });
}

void TPageControlSettings::startToClose() {
    HandlerSubscribers::remove("U1/FLASH/", SubscriberIDFLASH);
    HandlerSubscribers::remove("U1/RAM/", SubscriberIDRAM);
    TagList->Clear();
    isOpen = false;
}

bool TPageControlSettings::ProcessMessage(TMessage* m) {
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

TVisualObject* TPageControlSettings::getSignalOfFocusedChild() {
    for (auto& element : Container->List) {
        TVisualObject* e = element->getFocusedElement();
        TParameter* p = (e) ? (TParameter*)e->getDataSrc() : nullptr;
        if (p) return e;
    }
    return nullptr;
}

void TPageControlSettings::fillPageContainer(void) {
    TagList->Clear();
    TLabelInitStructure LabelInit;
    LabelInit.style = LabelsStyle::WIDTH_FIXED;
    LabelInit.Rect = { 10, 10, 10, 70 };
    LabelInit.focused = false;
    TagList->AddList({
        new TTagLine("UsgRef", "U1/RAM/UsgRef/", LabelInit),
        new TTagLine("StRef", "U1/RAM/StRef/", LabelInit),
        new TTagLine("UstStC", "U1/RAM/UstStC/", LabelInit),
        new TTagLine("Ustat", "U1/RAM/Ustat/", LabelInit),
        new TTagLine("fIexcMax", "U1/FLASH/fIexcMax/", LabelInit),
        new TTagLine("SRef", "U1/FLASH/SRef/", LabelInit),
        //new TTagLine("U1/FLASH/RInslUp/", LabelInit),
        });
}

TPageControlSettings::TPageControlSettings(std::string Name)
    :TPage(Name) {
    TVerticalContainerProps props = { false };
    Container = new TVerticalContainer(props, {});
     
    TLabelInitStructure LabelInit;
    LabelInit.pOwner = Container;
    LabelInit.caption = "Авто режим";
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

void TPageControlSettings::SlotUpdateFLASH(TSlotHandlerArsg args) {
    SlotUpdate("/FLASH", args);
}

void TPageControlSettings::SlotUpdateRAM(TSlotHandlerArsg args){
    SlotUpdate("/RAM", args);
}

void TPageControlSettings::SlotUpdate(const char* sector, TSlotHandlerArsg args){
    for(auto& e : TagList->List){
        TTagLine* tag = (TTagLine*)e;
        if((tag->Tag.find(sector)) != std::string::npos){
            TParameter* p = (TParameter*)tag->getDataSrc();
            tag->Value->setCaption(p->getValue(args, ""));
        }
    }
    Msg::send_message((u32)EventSrc::REPAINT, 0, 0);
}

TPageControlSettings::~TPageControlSettings() {
    TagList->Clear();
    Container->Clear();
    delete Container;
};
