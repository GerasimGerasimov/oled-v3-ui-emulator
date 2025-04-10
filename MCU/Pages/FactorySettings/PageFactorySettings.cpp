#include "PageFactorySettings.h"
#include "TagLineScrollCaptionComment.h"
#include <FixedHeader.h>
#include "Router.h"

TPageFactorySettings::TPageFactorySettings(std::string Name) : TPage(Name){
    TVerticalContainerProps props = {true};
    Container = new TVerticalContainer(props, {});

    TLabelInitStructure LabelInit;
    LabelInit.pOwner = Container;
    LabelInit.caption = "Заводские уставки";
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

TPageFactorySettings::~TPageFactorySettings(){
    TagList->Clear();
    Container->Clear();
    delete Container;
}

void TPageFactorySettings::onOpen(){
    fillPageContainer();
    fillValue();
}

void TPageFactorySettings::view(){
    Container->view();
}

bool TPageFactorySettings::ProcessMessage(TMessage* m){
    TVisualObject* e = {nullptr};
    switch(m->Event){
    case (u32)EventSrc::KEYBOARD: {
        switch(m->p1){
        case (u32)KeyCodes::ESC:
            TRouter::setTask({false, "MainMenu", nullptr});
            break;
        case (u32)KeyCodes::ENT:
            return false;
        case (u32)KeyCodes::F2:
            TRouter::PageValueEditEntryData.backPage = Name;
            TRouter::setTask({false, "FactorySettingsEdit", nullptr});
            break;
        }
    }
    }
    for(auto& element : List){
        element->ProcessMessage(m);
    }
    return false;
}

void TPageFactorySettings::startToClose(){
    TagList->Clear();
    isOpen = false;
}

void TPageFactorySettings::fillPageContainer(){
    TagList->Clear();
    TLabelInitStructure LabelInit;
    LabelInit.style = LabelsStyle::WIDTH_FIXED;
    LabelInit.Rect = {10, 10, 10, 70};
    LabelInit.focused = false;
    TagList->AddList({
        new TTagLineScrollCaptionComment("U1/FLASH/R1-DT1/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/R2-DT2/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/tShu-Pr_On/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/tShu-Pr_Off/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/tShu-Av_On/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/tShu-Av_Off/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/tR-Pr_On/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/tR-Pr_Off/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/tR-Av_On/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/tR-Av_Off/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/T3-Ct2/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/T3-Ct3/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/T3-Ct4/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/T3-Ct5/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/T3-Ct6/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/T3-Ct7/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/T3-K/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/T3-Total/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/T3-MTZ_Rotor/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/T3-MTZ_Stator/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/VZNP/", LabelInit),
        });
}

void TPageFactorySettings::fillValue(){
    for(auto& e : TagList->List){
        TTagLine* tag = (TTagLine*)e;
        TParameter* p = (TParameter*)tag->getDataSrc();

        std::string hex = p->getValueFactory();
        tag->Value->setCaption(p->getHexToValue(hex));
    }
}
