#include "TPagePowerSupply.h"
#include "TagLineScrollCaptionComment.h"
#include <FixedHeader.h>
#include "Router.h"

TPagePowerSupply::TPagePowerSupply(std::string Name) : TPageControlSettings(Name) {
    TLabelInitStructure LabelInitH;
    LabelInitH.pOwner = Container;
    LabelInitH.caption = "Питание";
    TFixedHeader* pHeader = new TFixedHeader(LabelInitH);
    delete Container->List[0];
    Container->List[0] = pHeader;
}

void TPagePowerSupply::fillPageContainer() {
    TagList->Clear();
    TLabelInitStructure LabelInit;
    LabelInit.style = LabelsStyle::WIDTH_FIXED;
    LabelInit.Rect = { 10, 10, 10, 80 };
    LabelInit.focused = false;
    TagList->AddList({
        new TTagLine("FreqRect", "U1/RAM/FreqRect/", LabelInit),
        });
}
