#include "PageSelfExc.h"
#include "TagLineScrollCaptionComment.h"
#include <FixedHeader.h>

TPageSelfExc::TPageSelfExc(std::string Name) : TPageBasicSettings(Name){
    TLabelInitStructure LabelInitH;
    LabelInitH.pOwner = Container;
    LabelInitH.caption = "Самовозбуждение";
    TFixedHeader* pHeader = new TFixedHeader(LabelInitH);
    delete Container->List[0];
    Container->List[0] = pHeader;
}

void TPageSelfExc::fillPageContainer(){
    TagList->Clear();
    TLabelInitStructure LabelInit;
    LabelInit.style = LabelsStyle::WIDTH_FIXED;
    LabelInit.Rect = {10, 10, 10, 70};
    LabelInit.focused = false;
    TagList->AddList({
        new TTagLine("SelfExciteEnable", "U1/FLASH/SelfExciteEnable/", LabelInit),
        new TTagLine("Ready_GS_ON", "U1/FLASH/Ready_GS_ON/", LabelInit),
        });
}
