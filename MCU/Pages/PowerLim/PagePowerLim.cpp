#include "PagePowerLim.h"
#include "TagLineScrollCaptionComment.h"
#include <FixedHeader.h>

TPagePowerLim::TPagePowerLim(std::string Name) : TPageControlSettings(Name){
    TLabelInitStructure LabelInitH;
    LabelInitH.pOwner = Container;
    LabelInitH.caption = "Огранич. мощности";
    TFixedHeader* pHeader = new TFixedHeader(LabelInitH);
    delete Container->List[0];
    Container->List[0] = pHeader;
}

void TPagePowerLim::fillPageContainer(){
    TagList->Clear();
    TLabelInitStructure LabelInit;
    LabelInit.style = LabelsStyle::WIDTH_FIXED;
    LabelInit.Rect = {10, 10, 10, 80};
    LabelInit.focused = false;
    TagList->AddList({
        new TTagLineScrollCaptionComment("U1/RAM/Qsg/", LabelInit),
        new TTagLineScrollCaptionComment("U1/RAM/Qoe/", LabelInit),
        new TTagLineScrollCaptionComment("U1/RAM/QLimMin/", LabelInit),
        new TTagLineScrollCaptionComment("U1/RAM/QLimMax/", LabelInit),

        new TTagLineScrollCaptionComment("U1/FLASH/Pnom/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/QminP0/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/QminP1/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/QmaxP0/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/QmaxP1/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/dQmin/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/QminAsyncTime/", LabelInit),
        });
}
