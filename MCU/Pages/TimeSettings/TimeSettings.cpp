#include "TimeSettings.h"
#include "TagLineScrollCaptionComment.h"
#include <FixedHeader.h>

TTimeSettings::TTimeSettings(std::string Name) : TPageBasicSettings(Name){
    TLabelInitStructure LabelInitH;
    LabelInitH.pOwner = Container;
    LabelInitH.caption = "Уставки времени";
    TFixedHeader* pHeader = new TFixedHeader(LabelInitH);
    delete Container->List[0];
    Container->List[0] = pHeader;
}

void TTimeSettings::fillPageContainer(){
    TagList->Clear();
    TLabelInitStructure LabelInit;
    LabelInit.style = LabelsStyle::WIDTH_FIXED;
    LabelInit.Rect = {10, 10, 10, 70};
    LabelInit.focused = false;
    TagList->AddList({
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
