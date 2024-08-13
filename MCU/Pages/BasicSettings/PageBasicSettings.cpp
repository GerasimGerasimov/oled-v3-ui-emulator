#include "PageBasicSettings.h"
#include "Router.h"
#include "TagLineScrollCaption.h"
#include "TagLineVarSize.h"
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
    LabelInit.Rect = { 10, 10, 10, 70 };
    LabelInit.focused = false;
    TagList->AddList({
        new TTagLineScrollCaption("Пуск принудительный", "U1/FLASH/EnforcedStart/", LabelInit),
        new TTagLineScrollCaption("t тяжелого пуска", "U1/FLASH/HsTime/", LabelInit),
        new TTagLineScrollCaption("t пуска форсировки", "U1/FLASH/StartForceTime/", LabelInit),
        new TTagLineScrollCaption("Ток форсировки", "U1/FLASH/IExcForce/", LabelInit),
        new TTagLine("Ток возб.", "U1/FLASH/IExcRef/", LabelInit),
        new TTagLineVarSize("Пуск по току", "U1/FLASH/IstStart/", LabelInit, 0),
        new TTagLineVarSize("Стоп по току", "U1/FLASH/IstStop/", LabelInit, 0),
        new TTagLine("Ток статора", "U1/FLASH/IstExcEnable/", LabelInit),
        new TTagLineScrollCaption("Min частота скольжения", "U1/FLASH/ExcEnableFreq/", LabelInit),
        new TTagLineScrollCaption("Частота тяжелого пуска", "U1/FLASH/HsFreq/", LabelInit),
    });
}

TPageBasicSettings::TPageBasicSettings(std::string Name)
    :TPage(Name) {
    TVerticalContainerProps props = { false };
    Container = new TVerticalContainer(props, {});

    TLabelInitStructure LabelInit;
    LabelInit.pOwner = Container;
    LabelInit.caption = "Пуск";
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
