#include "PageFactorySettingsEdit.h"
#include "Router.h"
#include <IniResources.h>
#include <FixedHeader.h>
#include "parameters.h"
#include "AppModbusSlave.h"
#include "Slot.h"

TVisualObject* TPageFactorySettingsEdit::getSignalOfFocusedChild(){
    for(auto& element : Container->List){
        TVisualObject* e = element->getFocusedElement();
        //TParameter* p = (e) ? (TParameter*)e->getDataSrc() : nullptr;
        if(e) return e;
    }
    return nullptr;
}

void TPageFactorySettingsEdit::sendSetting(){
    std::map<std::string, ISignal*>* sector = IniResources::getSectionMap("U1/FLASH/");
    std::map<u16, std::string> regData;
    if(sector){
        for(auto& n : *sector){
            std::string str = n.first;
            TParameter* p = static_cast<TParameter*>(n.second);
            std::string valueFactory = p->getValueFactory();
            std::string addrHex = p->getRegHexAddr();
            u16 addr = static_cast<u16>(std::stoul(addrHex, nullptr, 16));
            regData[addr] = valueFactory;
        }
        ModbusSlave::setSetting(regData,  "U1", "FLASH", [this](Slot* slot, u8* reply){ SlotUpdate(slot, reply); });
    }
}

void TPageFactorySettingsEdit::SlotUpdate(Slot* slot, u8* reply){
    if(slot){
        slot->Flags |= (u16)SlotStateFlags::SKIP_SLOT;
    }
}

TPageFactorySettingsEdit::TPageFactorySettingsEdit(std::string Name) : TPage(Name){
    TVerticalContainerProps props = {false};
    Container = new TVerticalContainer(props, {});

    TLabelInitStructure LabelInit;
    LabelInit.pOwner = Container;
    LabelInit.caption = "Сброс всех уставок";
    TFixedHeader* pHeader = new TFixedHeader(LabelInit);
    Container->Add(pHeader);

    props = {true};
    TagList = new TVerticalContainer(props, {});
    TagList->ElementRect = {0, 0,
                            (u16)(VIEW_PORT_MAX_HEIGHT - pHeader->getHeight() - 1),
                            VIEW_PORT_MAX_WIDTH};
    Container->Add(TagList);

    AddList({Container});
}

TPageFactorySettingsEdit::~TPageFactorySettingsEdit(){
    TagList->Clear();
    Container->Clear();
    delete Container;
}

void TPageFactorySettingsEdit::onOpen(){
    fillPageContainer();
}

void TPageFactorySettingsEdit::view(){
    Container->view();
}

bool TPageFactorySettingsEdit::ProcessMessage(TMessage* m){
    TVisualObject* e = {nullptr};
    switch(m->Event){
        case (u32)EventSrc::KEYBOARD: {
            switch(m->p1){
                case (u32)KeyCodes::ESC:
                    TRouter::setTask({false, TRouter::getBackPage(), nullptr});
                    break;
                case (u32)KeyCodes::ENT:
                    e = getSignalOfFocusedChild();
                    if(e){
                        if(static_cast<TLabel*>(e)->getCaption() == "Да"){
                            sendSetting();
                        }

                        TRouter::setTask({false, TRouter::getBackPage(), nullptr});

                    }
                    break;
                }
            }
    }
    for(auto& element : List){
        element->ProcessMessage(m);
    }
    return false;
}

void TPageFactorySettingsEdit::startToClose(){
    TagList->Clear();
    isOpen = false;
}

void TPageFactorySettingsEdit::fillPageContainer(){
    TagList->Clear();
    TLabelInitStructure LabelInit;
    LabelInit.style = LabelsStyle::WIDTH_FIXED;
    LabelInit.Rect = {10, 10, 10, 65};
    LabelInit.focused = false;
    LabelInit.caption = "Да";
    std::vector <TVisualObject*> data;
    data.push_back(new TLabel(LabelInit));
    LabelInit.caption = "Нет";
    data.push_back(new TLabel(LabelInit));
    TagList->AddList(data);
}
