#include "PageControlVoltageStator.h"
#include "TagLineScrollCaptionComment.h"
#include <FixedHeader.h>

TPageControlVoltageStator::TPageControlVoltageStator(std::string Name) : TPageControlSettings(Name){
    TLabelInitStructure LabelInitH;
    LabelInitH.pOwner = Container;
    LabelInitH.caption = "Напр. статора";
    TFixedHeader* pHeader = new TFixedHeader(LabelInitH);
    delete Container->List[0];
    Container->List[0] = pHeader;
}

void TPageControlVoltageStator::fillPageContainer(){
    TagList->Clear();
    TLabelInitStructure LabelInit;
    LabelInit.style = LabelsStyle::WIDTH_FIXED;
    LabelInit.Rect = {10, 10, 10, 80};
    LabelInit.focused = false;
    TagList->AddList({
        new TTagLineScrollCaptionComment("U1/RAM/Ustat/", LabelInit),
        new TTagLineScrollCaptionComment("U1/RAM/UstLow/", LabelInit),
        new TTagLineScrollCaptionComment("U1/RAM/UstFail/", LabelInit),

        new TTagLineScrollCaptionComment("U1/FLASH/UstNom/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/UstLowReset/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/UstLowSet/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/UstFailReset/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/UstFailSet/", LabelInit),
        });
}
