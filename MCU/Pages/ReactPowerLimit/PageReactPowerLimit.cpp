#include "PageReactPowerLimit.h"
#include "TagLineScrollCaptionComment.h"
#include <FixedHeader.h>

TPageReactPowerLimit::TPageReactPowerLimit(std::string Name) : TPageBasicSettings(Name){
    TLabelInitStructure LabelInitH;
    LabelInitH.pOwner = Container;
    LabelInitH.caption = "Огран. реакт. мощ.";
    TFixedHeader* pHeader = new TFixedHeader(LabelInitH);
    delete Container->List[0];
    Container->List[0] = pHeader;
}

void TPageReactPowerLimit::fillPageContainer(void){
    TagList->Clear();
    TLabelInitStructure LabelInit;
    LabelInit.style = LabelsStyle::WIDTH_FIXED;
    LabelInit.Rect = {10, 10, 10, 70};
    LabelInit.focused = false;
    TagList->AddList({
        new TTagLineScrollCaptionComment("U1/FLASH/Pnom/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/QminP0/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/QminP1/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/dQmin/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/QmaxP0/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/QmaxP1/", LabelInit),
        });
}
