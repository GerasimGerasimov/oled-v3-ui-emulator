#include "PagePower.h"
#include "TagLineScrollCaptionComment.h"
#include "FixedHeader.h"

TPagePower::TPagePower(std::string Name) : TPageSensors(Name){
    TLabelInitStructure LabelInitH;
    LabelInitH.pOwner = Container;
    LabelInitH.caption = "Мощность";
    TFixedHeader* pHeader = new TFixedHeader(LabelInitH);
    delete Container->List[0];
    Container->List[0] = pHeader;
}

void TPagePower::fillPageContainer(void){
    TagList->Clear();
    TLabelInitStructure LabelInit;
    LabelInit.style = LabelsStyle::WIDTH_FIXED;
    LabelInit.Rect = {10, 10, 10, 70};
    LabelInit.focused = false;

    TagList->AddList({
        new TTagLineScrollCaptionComment("U1/RAM/Ssg/", LabelInit),
        new TTagLineScrollCaptionComment("U1/RAM/Psg/", LabelInit),
        new TTagLineScrollCaptionComment("U1/RAM/Qsg/", LabelInit),
        new TTagLineScrollCaptionComment("U1/RAM/Qoe/", LabelInit),
        new TTagLineScrollCaptionComment("U1/RAM/QLimMin/", LabelInit),
        new TTagLineScrollCaptionComment("U1/RAM/QLimMax/", LabelInit),
        });
}
