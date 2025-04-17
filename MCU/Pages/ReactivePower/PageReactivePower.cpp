#include "PageReactivePower.h"
#include "TagLineScrollCaptionComment.h"
#include <FixedHeader.h>

TPageReactivePower::TPageReactivePower(std::string Name) : TPageSensors(Name){
    TLabelInitStructure LabelInitH;
    LabelInitH.pOwner = Container;
    LabelInitH.caption = "Реактивная мощность";
    TFixedHeader* pHeader = new TFixedHeader(LabelInitH);
    delete Container->List[0];
    Container->List[0] = pHeader;
}

void TPageReactivePower::fillPageContainer(){
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
        });
}
