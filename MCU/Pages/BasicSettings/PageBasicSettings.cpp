#include "PageBasicSettings.h"
#include "Router.h"
#include "TagLine.h"
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
    LabelInit.style = LabelsStyle::WIDTH_DINAMIC;
    LabelInit.Rect = { 10, 10, 10, 10 };
    LabelInit.focused = false;
    TagList->AddList({
        new TTagLine("IÑgMin", "U1/FLASH/IchargeMin/", LabelInit),
        new TTagLine("IÑgMax", "U1/FLASH/IchargeMax/", LabelInit),
        new TTagLine("UCgMax", "U1/FLASH/UchargeMax/", LabelInit),
        new TTagLine("IAddCg", "U1/FLASH/IAddCharge/", LabelInit),
        new TTagLine("tAddCg", "U1/FLASH/tAddCharge/", LabelInit),
        new TTagLine("IEqCgMin", "U1/FLASH/IEqualChargeMin/", LabelInit),
        new TTagLine("IEqCgMax", "U1/FLASH/IEqualChargeMax/", LabelInit),
        new TTagLine("UEqCgMax", "U1/FLASH/UEqualChargeMax/", LabelInit),
        new TTagLine("IEqAddCg", "U1/FLASH/IEqualAddCharge/", LabelInit),
        new TTagLine("tEqAddCg", "U1/FLASH/tEqualAddCharge/", LabelInit),
        new TTagLine("tEqChg", "U1/FLASH/tEqualCharge/", LabelInit),
        new TTagLine("UDischarge", "U1/FLASH/UdischargeMin/", LabelInit),
        new TTagLine("Idischarge", "U1/FLASH/IdischargeMin/", LabelInit),
        new TTagLine("kRegU", "U1/FLASH/kRegU/", LabelInit),
        new TTagLine("kRegI", "U1/FLASH/kRegI/", LabelInit),
        new TTagLine("TiReg", "U1/FLASH/TiReg/", LabelInit),
        new TTagLine("AKBsize", "U1/FLASH/BatteryCapacity/", LabelInit),
        new TTagLine("tStart", "U1/FLASH/tSoftStart/", LabelInit),
    });
}

TPageBasicSettings::TPageBasicSettings(std::string Name)
    :TPage(Name) {
    TVerticalContainerProps props = { false };
    Container = new TVerticalContainer(props, {});

    TLabelInitStructure LabelInit;
    LabelInit.pOwner = Container;
    LabelInit.caption = "Îñíîâíûå óñòàâêè";
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
