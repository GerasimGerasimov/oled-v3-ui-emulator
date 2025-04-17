#include "PageVoltageLim.h"
#include "TagLineScrollCaptionComment.h"
#include <FixedHeader.h>

TPageVoltageLim::TPageVoltageLim(std::string Name) : TPageControlSettings(Name){
    TLabelInitStructure LabelInitH;
    LabelInitH.pOwner = Container;
    LabelInitH.caption = "Огранич. напряж.";
    TFixedHeader* pHeader = new TFixedHeader(LabelInitH);
    delete Container->List[0];
    Container->List[0] = pHeader;
}

void TPageVoltageLim::fillPageContainer(){
    TagList->Clear();
    TLabelInitStructure LabelInit;
    LabelInit.style = LabelsStyle::WIDTH_FIXED;
    LabelInit.Rect = {10, 10, 10, 80};
    LabelInit.focused = false;
    TagList->AddList({
        new TTagLineScrollCaptionComment("U1/RAM/Ustat/", LabelInit),
        new TTagLineScrollCaptionComment("U1/RAM/UsgRef/", LabelInit),
        new TTagLineScrollCaptionComment("U1/RAM/UstStC/", LabelInit),

        new TTagLineScrollCaptionComment("U1/FLASH/UstLmax/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/UstLmin/", LabelInit),
        });
}
