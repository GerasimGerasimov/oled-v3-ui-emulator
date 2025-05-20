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
   // currentIndicator2.stateValue();
}
void TPageHome::onOpen() {
    //fillPageContainer();
    TGrahics::Line(40, 0, 40, 63, 1);
    TGrahics::Line(41, 0, 41, 63, 1);
    TGrahics::Line(82, 0, 82, 63, 1);
    TGrahics::Line(99, 0, 99, 63, 1);
   
    //TGrahics::outTextVertical("1200", x + 21, y + 8, std::fabs(colorState - 1), "Verdana12");
    
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
                    //TRouter::setTask({ false, "MainMenu", nullptr });
                    currentIndicator1.invertStateColor();
                    
                   
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
                case (u32)KeyCodes::Up:
                    
                    currentIndicator1.setValue(currentIndicator1.getValue() + 85);
                    //currentIndicator2.setValue(currentIndicator1.getValue() + 5);
                    break;

                case (u32)KeyCodes::Right: 
                    currentIndicator1.invertStateColor();
                   // currentIndicator2.invertStateColor(1);
                   //currentIndicator1.invertStateColor(1);
                   operatingMode.stateValue(1);

                    break;

                case (u32)KeyCodes::Left: 
                    operatingMode.stateValue(1);
                    currentIndicator1.invertStateColor();
                    //currentIndicator1.invertStateColor(1);
                    //currentIndicator2.invertStateColor(1);
                    //groupIndicators.invertOut();
                    break;

                case (u32)KeyCodes::Down: 
                    currentIndicator1.setValue(currentIndicator1.getValue() - 85);

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

TPageHome::TPageHome(std::string Name) :TPage(Name), currentIndicator1(0,0, "I, mA", "Iref",  0), currentIndicator2(42, 0, "U, kV", "Uref", 0), operatingMode(83, 0, 0), groupIndicators(100, 0, 0)
{
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
