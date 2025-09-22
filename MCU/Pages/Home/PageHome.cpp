#include "PageHome.h"
#include "Router.h"
#include "TagLine.h"
#include <IniResources.h>

void TPageHome::view() {
   // TagList->view();
    IndicatorU.view();
    IndicatorI.view();
    groupIndicators.view();
};

void TPageHome::onOpen() {
    TGrahics::Line(40, 0, 40, 63, 1);
    TGrahics::Line(81, 0, 81, 63, 1);
    //fillPageContainer();
    SubscriberID = HandlerSubscribers::set("U1/RAM/", [this](TSlotHandlerArsg args) { SlotUpdateRAM(args); });
    SubIDFlash = HandlerSubscribers::set("U1/FLASH/", [this](TSlotHandlerArsg args) { SlotUpdateFLASH(args); });
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
            TRouter::PageValueEditEntryData.backPage = Name;
            if (e) {
                ISignal* p = IniResources::getSignalByTag(((TTagLine*)(e))->Tag);
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
            container[component]->inFocus = false;
            break;
        case (u32)KeyCodes::Right:
            container[component]->inFocus = false;
            if (component < container.size() - 1) {
                component++;
                container[component]->inFocus = true;
            }
            else {
                container[component]->inFocus = true;
            }
            break;

        case (u32)KeyCodes::Left:
            container[component]->inFocus = false;
            if (component > 0) {
                component--;
                container[component]->inFocus = true;
            }
            else {
                container[component]->inFocus = true;
            }
            break;
        }
    }
    }

    for (auto& element : container) {
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
    LabelInit.style = LabelsStyle::WIDTH_DINAMIC;
    LabelInit.Rect = { 10, 10, 10, 10 };
    LabelInit.focused = false;
    LabelInit.caption = "Стартовый экран";
    TagList->AddList({
        /*new TTagLine("Uref", "U1/RAM/Uref/", LabelInit),
        new TTagLine("Ilim", "U1/RAM/Ilim/", LabelInit),
        new TTagLine("Uout", "U1/RAM/Uout/", LabelInit),
        new TTagLine("Iout", "U1/RAM/Iout/", LabelInit),
        new TTagLine("tRun", "U1/RAM/tRun/", LabelInit),
        new TTagLine("WRun", "U1/RAM/WRun/", LabelInit),*/
        //new TTagLineScrollCaptionComment("U1/FLASH/tSoftStart/", LabelInit),
        //new TLabel(LabelInit)
    });
    
}

TPageHome::TPageHome(std::string Name)
    :TPage(Name), 
    IndicatorU(0, 0, 0, "Uout,V", "Uref", "U1/RAM/Uout/", "U1/RAM/Uref/", "U1/FLASH/UrefMax/", "U1/FLASH/UrefMin/", "U1/FLASH/Ustep/", "U1/FLASH/UoutMax/"), 
    IndicatorI(41, 0, 0, "Iout,A", "Ilim", "U1/RAM/Iout/", "U1/RAM/Ilim/", "U1/FLASH/IlimDefault/", "U1/FLASH/IlimDefault/", "U1/FLASH/Istep/", "U1/FLASH/IoutMTZ/"),
    groupIndicators(82, 0, 0, "U1/RAM/Run/", "U1/RAM/tRun/", "U1/RAM/WRun/") {
    TVerticalContainerProps props = { false };
    container = { &IndicatorU, &IndicatorI, &groupIndicators };

    TagList = new TVerticalContainer(props, {});
    AddList({ TagList });
};

void TPageHome::SlotUpdate(const char* sector, TSlotHandlerArsg args) {
    for (auto& e : container) {
        e->updateObj(sector, args, "");

    }
    //currentIndicator1.updateValueRef(args, "");
    //groupIndicators.update(args, "");
    Msg::send_message((u32)EventSrc::REPAINT, 0, 0);
}

void TPageHome::SlotUpdateFLASH(TSlotHandlerArsg args) {
    SlotUpdate("FLASH", args);
}

void TPageHome::SlotUpdateRAM(TSlotHandlerArsg args) {
    SlotUpdate("RAM", args);
}

TPageHome::~TPageHome() {
    TagList->Clear();
    delete TagList;
};
