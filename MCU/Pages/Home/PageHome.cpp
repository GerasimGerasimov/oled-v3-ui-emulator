#include "PageHome.h"
#include "Router.h"
#include "TagLine.h"
#include <IniResources.h>
#include <iostream>

void TPageHome::view() {
    //TagList->view();
    currentIndicator1.view();
    currentIndicator2.view();
    groupIndicators.view();
    operatingMode.view();
}
void TPageHome::onOpen() {
    TGrahics::Line(42, 0, 42, 63, 1);
    TGrahics::Line(85, 0, 85, 63, 1);
    TGrahics::Line(86, 31, 126, 31, 1);
    //TGrahics::Line(99, 0, 99, 63, 1);
    SubscriberID = HandlerSubscribers::set("U1/RAM/", [this](TSlotHandlerArsg args) { SlotUpdateRAM(args); });
    SubIDFlash = HandlerSubscribers::set("U1/FLASH/", [this](TSlotHandlerArsg args) { SlotUpdateFLASH(args); });
}

void TPageHome::startToClose() {
    HandlerSubscribers::remove("U1/RAM/", SubscriberID);
    HandlerSubscribers::remove("U1/FLASH/", SubIDFlash);
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
                /*case (u32)KeyCodes::ENT:
                    e = getSignalOfFocusedChild();
                    if (e) {
                        TRouter::PageValueEditEntryData.tag = ((TTagLine*)(e))->Tag;
                        TRouter::PageValueEditEntryData.value = ((TTagLine*)(e))->Value->getCaption();
                        TRouter::PageValueEditEntryData.backPage = Name;
                        TRouter::setTask({ false, "EditValue", nullptr });
                    }
                    container[currentComponent]->inFocus = false;
                    break;*/
                case (u32)KeyCodes::Right: 
                    container[currentComponent]->inFocus = false;
                    if (currentComponent < container.size() - 1) {
                        currentComponent++;
                        container[currentComponent]->startEdit();
                    }
                    else {
                        container[currentComponent]->startEdit();
                    }
                    break;

                case (u32)KeyCodes::Left: 
                    container[currentComponent]->inFocus = false;
                    if (currentComponent > 0) {
                        currentComponent--;
                        container[currentComponent]->startEdit();
                    }
                    else {
                        container[currentComponent]->startEdit();
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
        //new TTagLine("TiReg", "U1/FLASH/TiReg/", LabelInit),
        //new TTagLineScrollCaptionComment("U1/FLASH/tSoftStart/", LabelInit),
        new TLabel(LabelInit)
    });
    
}

TPageHome::TPageHome(std::string Name) :TPage(Name), 
    currentIndicator1(0, 0, "I, A", "Iref", "U1/RAM/Iout/", "U1/FLASH/Iref/", 0, "U1/FLASH/Ilimit/", "U1/FLASH/Ioverload/", "U1/FLASH/IrefStep/"),
    currentIndicator2(43, 0, "U, V", "Uref", "U1/RAM/Uout/", "U1/FLASH/Uref/",0, "U1/FLASH/Ulimit/", "U1/FLASH/Ioverload/", "U1/FLASH/UrefStep/"),
    operatingMode(86, 0, 0, "U1/RAM/mode/"),
    groupIndicators(86, 32, 0, "U1/RAM/RunTime/")

{
    container = { &currentIndicator1, &currentIndicator2, &operatingMode, &groupIndicators};
    TVerticalContainerProps props = { false };
    TagList = new TVerticalContainer(props, {});
    AddList({ TagList });
    
};

void TPageHome::SlotUpdate(const char* sector, TSlotHandlerArsg args) {
    for (auto& e : container) {
        e->updateObj(sector, args, "");
    }
    //currentIndicator1.updateValueRef(args, "");
    groupIndicators.update(args, "");
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

