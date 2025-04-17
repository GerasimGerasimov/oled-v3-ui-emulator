#include "PageCurrentLim.h"
#include "TagLineScrollCaptionComment.h"
#include <FixedHeader.h>

TPageCurrentLim::TPageCurrentLim(std::string Name) : TPageControlSettings(Name){
    TLabelInitStructure LabelInitH;
    LabelInitH.pOwner = Container;
    LabelInitH.caption = "Ограничетели токов";
    TFixedHeader* pHeader = new TFixedHeader(LabelInitH);
    delete Container->List[0];
    Container->List[0] = pHeader;
}

void TPageCurrentLim::fillPageContainer(){
    TagList->Clear();
    TLabelInitStructure LabelInit;
    LabelInit.style = LabelsStyle::WIDTH_FIXED;
    LabelInit.Rect = {10, 10, 10, 80};
    LabelInit.focused = false;
    TagList->AddList({
        new TTagLineScrollCaptionComment("U1/RAM/Iexc/", LabelInit),
        new TTagLineScrollCaptionComment("U1/RAM/IexcLimMax/", LabelInit),
        new TTagLineScrollCaptionComment("U1/RAM/IexcLimMin/", LabelInit),

        new TTagLineScrollCaptionComment("U1/FLASH/fIexcMin/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/fIexcMax/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/fIexcForce/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/Iref_i2t_R_limit/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/i2tOV_OFF_R/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/i2tOV_ON_R/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/Ti2tR/", LabelInit),
        });
}
