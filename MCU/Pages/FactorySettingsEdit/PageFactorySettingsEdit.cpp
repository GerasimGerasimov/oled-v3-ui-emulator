#include "PageFactorySettingsEdit.h"
#include "Router.h"
#include <IniResources.h>
#include <FixedHeader.h>
#include "parameters.h"

TVisualObject* TPageFactorySettingsEdit::getSignalOfFocusedChild(){
    for(auto& element : Container->List){
        TVisualObject* e = element->getFocusedElement();
        //TParameter* p = (e) ? (TParameter*)e->getDataSrc() : nullptr;
        if(e) return e;
    }
    return nullptr;
}

void TPageFactorySettingsEdit::sendSetting(){
}

TPageFactorySettingsEdit::TPageFactorySettingsEdit(std::string Name) : TPage(Name){
    TVerticalContainerProps props = {false};
    Container = new TVerticalContainer(props, {});

    TLabelInitStructure LabelInit;
    LabelInit.pOwner = Container;
    LabelInit.caption = "Переписать уставки";
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
