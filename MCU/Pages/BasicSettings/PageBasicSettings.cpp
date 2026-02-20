#include "PageBasicSettings.h"
#include "Router.h"
#include "TagLine.h"
#include "TagLineScrollCaptionComment.h"
#include <IniResources.h>
#include <FixedHeader.h>

void TPageBasicSettings::view() {
    Container->view();
};

void TPageBasicSettings::onOpen() {
    fillPageContainer();
    SubscriberID = HandlerSubscribers::set("U1/FLASH/", [this](TSlotHandlerArsg args) { SlotUpdate(args); });
}

void TPageBasicSettings::startToClose() {
    HandlerSubscribers::remove("U1/FLASH/", SubscriberID);
    TagList->Clear();
    isOpen = false;
}

bool TPageBasicSettings::ProcessMessage(TMessage* m) {
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

TVisualObject* TPageBasicSettings::getSignalOfFocusedChild() {
    for (auto& element : Container->List) {
        TVisualObject* e = element->getFocusedElement();
        TParameter* p = (e) ? (TParameter*) e->getDataSrc() : nullptr;
        if (p) return e;
    }
    return nullptr;
}

void TPageBasicSettings::fillPageContainer(void) {
    TagList->Clear();
    TLabelInitStructure LabelInit;
    LabelInit.style = LabelsStyle::WIDTH_FIXED;
    LabelInit.Rect = { 10, 10, 10, 70};
    LabelInit.focused = false;

    TagList->AddList({
        new TTagLine("UrefDefault", "U1/FLASH/UrefDefault/", LabelInit),
        new TTagLine("UrefDefaultR", "U1/FLASH/UrefDefaultR/", LabelInit),
        new TTagLine("IrefDefault", "U1/FLASH/IrefDefault/", LabelInit),
        new TTagLine("IrefDefaultR", "U1/FLASH/IrefDefaultR/", LabelInit),
        new TTagLine("DIrefDefault", "U1/FLASH/DIrefDefault/", LabelInit),
        new TTagLine("DIrefDefaultR", "U1/FLASH/DIrefDefaultR/", LabelInit),
        new TTagLine("Ulimit", "U1/FLASH/Ulimit/", LabelInit),
        new TTagLine("Ilimit", "U1/FLASH/Ilimit/", LabelInit),
        new TTagLine("UlimitR", "U1/FLASH/UlimitR/", LabelInit),
        new TTagLine("IlimitR", "U1/FLASH/IlimitR/", LabelInit),
        new TTagLine("tSoftStart", "U1/FLASH/tSoftStart/", LabelInit),
        new TTagLine("TimeLimit", "U1/FLASH/TimeLimit/", LabelInit),
        new TTagLine("ChargeLimit", "U1/FLASH/ChargeLimit/", LabelInit),
        new TTagLine("UrefStep", "U1/FLASH/UrefStep/", LabelInit),
        new TTagLine("IrefStep", "U1/FLASH/IrefStep/", LabelInit),
        new TTagLine("DIrefStep","U1/FLASH/DIrefStep/", LabelInit),
        new TTagLine("DensityMode","U1/FLASH/DensityMode/", LabelInit),
        new TTagLine("ControlMode","U1/FLASH/ControlMode/", LabelInit),
        new TTagLine("LowInsulateLevel","U1/FLASH/LowInsulateLevel/", LabelInit),
        new TTagLine("AlarmInsulateLeve","U1/FLASH/AlarmInsulateLeve/", LabelInit)
        
    });
}

TPageBasicSettings::TPageBasicSettings(std::string Name)
    :TPage(Name) {
    TVerticalContainerProps props = { true };
    Container = new TVerticalContainer(props, {});

    TLabelInitStructure LabelInit;
    LabelInit.pOwner = Container;
    LabelInit.caption = "Уставки работы";
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

void TPageBasicSettings::SlotUpdate(TSlotHandlerArsg args) {
    for (auto& e : TagList->List) {
        TTagLine* tag = (TTagLine*)e;
        TParameter* p = (TParameter*)tag->getDataSrc();
        tag->Value->setCaption(p->getValue(args, ""));
    }
    Msg::send_message((u32)EventSrc::REPAINT, 0, 0);
}

TPageBasicSettings::~TPageBasicSettings() {
    TagList->Clear();
    Container->Clear();
    delete Container;
};
