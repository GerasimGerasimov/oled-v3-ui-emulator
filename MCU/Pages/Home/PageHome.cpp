#include "PageHome.h"
#include "Router.h"
#include "TagLine.h"
#include <IniResources.h>
#include <iostream>

void TPageHome::view() {
    //TagList->view();
    currentIndicator1.view();
    currentIndicator2.view();
    operatingMode.view();
    groupIndicators.view();
    //currentIndicator2.scaleBar();
}
void TPageHome::onOpen() {
    //fillPageContainer();
    TGrahics::Line(40, 0, 40, 63, 1);
    TGrahics::Line(41, 0, 41, 63, 1);
    TGrahics::Line(82, 0, 82, 63, 1);
    TGrahics::Line(99, 0, 99, 63, 1);
    SubscriberID = HandlerSubscribers::set("U1/RAM/", [this](TSlotHandlerArsg args) { SlotUpdate(args); });
    //SubIDFlash = HandlerSubscribers::set("U1/FLASH/", [this](TSlotHandlerArsg args) { SlotUpdate(args); });
}

void TPageHome::startToClose() {
    HandlerSubscribers::remove("U1/RAM/", SubscriberID);
    //HandlerSubscribers::remove("U1/FLASH", SubIDFlash);
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
                /*case (u32)KeyCodes::F1:
                    e = getSignalOfFocusedChild();
                    if (e) {
                        ISignal* p = IniResources::getSignalByTag(((TTagLine*)(e))->Tag);
                        TRouter::PageValueEditEntryData.backPage = Name;
                        TRouter::setTask({ false, "Help", p });
                    }
                    break;*/
                case (u32)KeyCodes::ENT:
                    e = getSignalOfFocusedChild();
                    if (e) {
                        TRouter::PageValueEditEntryData.tag = ((TTagLine*)(e))->Tag;
                        TRouter::PageValueEditEntryData.value = ((TTagLine*)(e))->Value->getCaption();
                        TRouter::PageValueEditEntryData.backPage = Name;
                        TRouter::setTask({ false, "EditValue", nullptr });
                    }
                    container[currentComponent]->inFocus = false;
                    break;
                case (u32)KeyCodes::Right: 
                    container[currentComponent]->inFocus = false;
                    if (currentComponent < container.size() - 1) {
                        currentComponent++;
                        container[currentComponent]->inFocus = true;
                    }
                    else {
                        container[currentComponent]->inFocus = true;
                    }
                    break;

                case (u32)KeyCodes::Left: 
                    container[currentComponent]->inFocus = false;
                    if (currentComponent > 0) {
                        currentComponent--;
                        container[currentComponent]->inFocus = true;
                    }
                    else {
                        container[currentComponent]->inFocus = true;
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
    currentIndicator1(0, 0, "I, mA", "Iref", "U1/RAM/IoutAve/", "U1/RAM/Iref/", 0, "U1/RAM/IvacUp_2/", "U1/RAM/RefInt/", 1),
    currentIndicator2(42, 0, "U, kV", "Uref", "U1/RAM/UoutAve/", "U1/RAM/Uref/",0, "U1/RAM/IvacUp_1/", "U1/RAM/RefInt/", 0.035),
    operatingMode(83, 0, 0), 
    groupIndicators(100, 0, 0, "U1/RAM/Out/", "U1/RAM/SparkFrq/")
{
    container = { &currentIndicator1, &currentIndicator2, &operatingMode};
    TVerticalContainerProps props = { false };
    TagList = new TVerticalContainer(props, {});
    AddList({ TagList });
    
};

void TPageHome::SlotUpdate(TSlotHandlerArsg args) {
    for (auto& e : container) {
        e->update(args, "");
    }
    groupIndicators.update(args, "");
    Msg::send_message((u32)EventSrc::REPAINT, 0, 0);
}

TPageHome::~TPageHome() {
    TagList->Clear();
    delete TagList;
};

