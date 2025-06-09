#include "PageSelfExc.h"
#include "TagLineScrollCaptionComment.h"
#include <FixedHeader.h>

TPageSelfExc::TPageSelfExc(std::string Name) : TPageBasicSettings(Name){
    TLabelInitStructure LabelInitH;
    LabelInitH.pOwner = Container;
    LabelInitH.caption = "Битовые уставки";
    TFixedHeader* pHeader = new TFixedHeader(LabelInitH);
    delete Container->List[0];
    Container->List[0] = pHeader;
}

void TPageSelfExc::fillPageContainer(){
    TagList->Clear();
    TLabelInitStructure LabelInit;
    LabelInit.style = LabelsStyle::WIDTH_FIXED;
    LabelInit.Rect = {10, 10, 10, 80};
    LabelInit.focused = false;
    TagList->AddList({
        new TTagLineScrollCaptionComment("U1/FLASH/Ready_GS_ON/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/RInslFltEnable/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/FltCCSB_QF5/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/FltMPS_QF1/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/FFE/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/SelfExciteEnable/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/IttAsymFltEnable/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/IstatOvrlFltEnable/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/BreakOffEnable/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/RotDiodNCFltEn/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/RotDiodSCFltEn/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/EnableiPB_Fault/", LabelInit),
        });
}
