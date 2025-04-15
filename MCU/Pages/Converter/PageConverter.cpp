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
        new TTagLine("Iexc", "U1/RAM/Iexc/", LabelInit),
        new TTagLine("Uexc", "U1/RAM/Uexc/", LabelInit),
        new TTagLine("Qpwm", "U1/RAM/Qpwm/", LabelInit),
        new TTagLine("IttA", "U1/RAM/IttA/", LabelInit),
        new TTagLine("IttB", "U1/RAM/IttB/", LabelInit),
        new TTagLine("IttC", "U1/RAM/IttC/", LabelInit),
        });
}
