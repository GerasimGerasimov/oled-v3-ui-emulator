#include "PageConverter.h"
#include "TagLineScrollCaptionComment.h"
#include <FixedHeader.h>

TPageConverter::TPageConverter(std::string Name) : TPageSensors(Name){
    TLabelInitStructure LabelInitH;
    LabelInitH.pOwner = Container;
    LabelInitH.caption = "Преобразователь";
    TFixedHeader* pHeader = new TFixedHeader(LabelInitH);
    delete Container->List[0];
    Container->List[0] = pHeader;
}

void TPageConverter::fillPageContainer(){
    TagList->Clear();
    TLabelInitStructure LabelInit;
    LabelInit.style = LabelsStyle::WIDTH_FIXED;
    LabelInit.Rect = {10, 10, 10, 70};
    LabelInit.focused = false;
    TagList->AddList({
        new TTagLineScrollCaptionComment("U1/RAM/Iexc/", LabelInit),
        new TTagLineScrollCaptionComment("U1/RAM/Uexc/", LabelInit),
        new TTagLineScrollCaptionComment("U1/RAM/Qpwm/", LabelInit),
        new TTagLineScrollCaptionComment("U1/RAM/IttA/", LabelInit),
        new TTagLineScrollCaptionComment("U1/RAM/IttB/", LabelInit),
        new TTagLineScrollCaptionComment("U1/RAM/IttC/", LabelInit),
        });
}
