#include "PageHome.h"
#include "Router.h"
#include "TagLineVarSize.h"
#include "TagCosLine.h"
#include "TagLineScrollCaptionComment.h"
#include <IniResources.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

void TPageHome::view() {
    TagList->view();
};

void TPageHome::onOpen() {
    fillPageContainer();
    SubscriberID = HandlerSubscribers::set("U1/RAM/", [this](TSlotHandlerArsg args) { SlotUpdate(args); });
}

void TPageHome::startToClose() {
    HandlerSubscribers::remove("U1/RAM/", SubscriberID);
    TagList->Clear();
    isOpen = false;
}

bool TPageHome::ProcessMessage(TMessage* m) {
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

TVisualObject* TPageHome::getSignalOfFocusedChild() {
    for (auto& element : List) {
        TVisualObject* e = element->getFocusedElement();
        TParameter* p = (e) ? (TParameter*) e->getDataSrc() : nullptr;
        if (p) return e;
    }
    return nullptr;
}

void TPageHome::fillPageContainer(void) {
    TagList->Clear();
    TLabelInitStructure LabelInit;
    LabelInit.style = LabelsStyle::WIDTH_FIXED;
    LabelInit.Rect = { 10, 10, 10, 70 };
    LabelInit.focused = false;


    TagList->AddList({
        new TTagLine("Ток ротора", "U1/RAM/Ir/", LabelInit),
        new TTagLine("Ток статора", "U1/RAM/Istat/", LabelInit),
        new TTagLineScrollCaption("Напряжение статора", "U1/RAM/Ustat/", LabelInit),
        new TTagCosLine("Cos угла Phi", "U1/RAM/F/", LabelInit),
        new TTagLineScrollCaption("Сопротивление изоляции", "U1/RAM/RINSL/ ", LabelInit),
        new TTagLineScrollCaptionComment("U1/RAM/Iq/", LabelInit)
        });
    int const totalTags = 6;
    for (int i = 0; i < totalTags; i++) {
        if (TTagLine* tagLine = dynamic_cast<TTagLine*>(TagList->List[i])) {
            tagLine->setValueLeft(70);
        }
    }
    for (int i = 0; i < totalTags; i++) {
        if (TTagLine* tagLine = dynamic_cast<TTagLine*>(TagList->List[i])) {
            tagLine->setMsuLeft(105);
        }
    }
}


TPageHome::TPageHome(std::string Name)
    :TPage(Name) {
    TVerticalContainerProps props = { false };
    TagList = new TVerticalContainer(props, {});
    AddList({ TagList });
};

void TPageHome::SlotUpdate(TSlotHandlerArsg args) {
    for (auto& e : TagList->List) {
        e->update(args, "");
    }
    Msg::send_message((u32)EventSrc::REPAINT, 0, 0);
}

TPageHome::~TPageHome() {
    TagList->Clear();
    delete TagList;
};
