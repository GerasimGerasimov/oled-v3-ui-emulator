#include "PageInsulResist.h"
#include "TagLineScrollCaptionComment.h"
#include <FixedHeader.h>

TPageInsulResist::TPageInsulResist(std::string Name) : TPageControlSettings(Name){
    TLabelInitStructure LabelInitH;
    LabelInitH.pOwner = Container;
    LabelInitH.caption = "Сопротив. изоляции";
    TFixedHeader* pHeader = new TFixedHeader(LabelInitH);
    delete Container->List[0];
    Container->List[0] = pHeader;
}

void TPageInsulResist::fillPageContainer(){
    TagList->Clear();
    TLabelInitStructure LabelInit;
    LabelInit.style = LabelsStyle::WIDTH_FIXED;
    LabelInit.Rect = {10, 10, 10, 80};
    LabelInit.focused = false;
    TagList->AddList({
        new TTagLineScrollCaptionComment("U1/RAM/RINSL/", LabelInit),
        new TTagLineScrollCaptionComment("U1/RAM/R_INSL_LOW/", LabelInit),
        new TTagLineScrollCaptionComment("U1/RAM/R_INSL_FLT/", LabelInit),

        new TTagLineScrollCaptionComment("U1/FLASH/RInslLow/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/RInslFlt/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/RInslUp/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/RInslFltEnable/", LabelInit),
        });
}
