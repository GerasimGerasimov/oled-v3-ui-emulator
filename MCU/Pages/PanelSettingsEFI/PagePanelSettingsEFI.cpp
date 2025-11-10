#include "PagePanelSettingsEFI.h"
#include "Router.h"
#include "TagLine.h"
#include "TagLineScrollCaptionComment.h"
#include "Router.h"
#include "TagLine.h"
#include <IniResources.h>
#include <FixedHeader.h>
#include "FlashData.h"
const static TSlotHandlerArsg FlashDataArg = {
    (u8*)&FLASH_DATA,
    255,
    0,
    255
};

void TPagePanelSettingsEFI::view() {
    Container->view();
};

void TPagePanelSettingsEFI::onOpen() {
    fillPageContainer();
}

void TPagePanelSettingsEFI::startToClose() {
    TagList->Clear();
    isOpen = false;
}


bool TPagePanelSettingsEFI::ProcessMessage(TMessage* m) {
    static u8 delay = 0;
    TVisualObject* e = { nullptr };
    switch (m->Event) {
    case (u32)EventSrc::TIMER:
        (delay)
            ? (delay--)
            : (SlotUpdate(FlashDataArg), delay = 10);
        break;
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

TVisualObject* TPagePanelSettingsEFI::getSignalOfFocusedChild() {
    for (auto& element : Container->List) {
        TVisualObject* e = element->getFocusedElement();
        TParameter* p = (e) ? (TParameter*)e->getDataSrc() : nullptr;
        if (p) return e;
    }
    return nullptr;
}

void TPagePanelSettingsEFI::fillPageContainer(void) {
    TagList->Clear();
    TLabelInitStructure LabelInit;
    LabelInit.style = LabelsStyle::WIDTH_DINAMIC;
    LabelInit.Rect = { 10, 10, 10, 10 };
    LabelInit.focused = false;

    TagList->AddList({
        new TTagLine("#1BPS", "U1/FLASH/RS485_1_BPS/", LabelInit),
        new TTagLine("#1ADR", "U1/FLASH/RS485_1_DVA/", LabelInit),
        new TTagLine("#1PRT", "U1/FLASH/RS485_1_PRTY/", LabelInit),
        new TTagLine("#1STP", "U1/FLASH/RS485_1_STOP/", LabelInit),
        new TTagLine("#2BPS", "U1/FLASH/RS485_2_BPS/", LabelInit),
        new TTagLine("#2ADR", "U1/FLASH/RS485_2_DVA/", LabelInit),
        new TTagLine("#2PRT", "U1/FLASH/RS485_2_PRTY/", LabelInit),
        new TTagLine("#2STP", "U1/FLASH/RS485_2_STOP/", LabelInit)
        });
}

TPagePanelSettingsEFI::TPagePanelSettingsEFI(std::string Name) :TPage(Name) {
    TVerticalContainerProps props = { false };
    Container = new TVerticalContainer(props, {});

    TLabelInitStructure LabelInitH;
    LabelInitH.pOwner = Container;
    LabelInitH.caption = "Настройки EFI";
    TFixedHeader* pHeader = new TFixedHeader(LabelInitH);
    Container->Add(pHeader);

    props = { true };
    TagList = new TVerticalContainer(props, {});
    TagList->ElementRect = { 0, 0,
                            (u16)(VIEW_PORT_MAX_HEIGHT - pHeader->getHeight() - 1),
                            VIEW_PORT_MAX_WIDTH };
    Container->Add(TagList);

    AddList({ Container });
};
void TPagePanelSettingsEFI::SlotUpdate(TSlotHandlerArsg args) {
    for (auto& e : TagList->List) {
        TTagLine* tag = (TTagLine*)e;
        TParameter* p = (TParameter*)tag->getDataSrc();
        tag->Value->setCaption(p->getValue(args, ""));
    }
    Msg::send_message((u32)EventSrc::REPAINT, 0, 0);
}

TPagePanelSettingsEFI::~TPagePanelSettingsEFI() {
    TagList->Clear();
    Container->Clear();
    delete Container;
};