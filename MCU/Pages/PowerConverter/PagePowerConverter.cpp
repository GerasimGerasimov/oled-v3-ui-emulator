#include "PagePowerConverter.h"
#include "TagLineScrollCaptionComment.h"
#include <FixedHeader.h>

TPagePowerConverter::TPagePowerConverter(std::string Name) : TPageControlSettings(Name){
    TLabelInitStructure LabelInitH;
    LabelInitH.pOwner = Container;
    LabelInitH.caption = "Питание преобразов.";
    TFixedHeader* pHeader = new TFixedHeader(LabelInitH);
    delete Container->List[0];
    Container->List[0] = pHeader;
}

void TPagePowerConverter::fillPageContainer(){
    TagList->Clear();
    TLabelInitStructure LabelInit;
    LabelInit.style = LabelsStyle::WIDTH_FIXED;
    LabelInit.Rect = {10, 10, 10, 80};
    LabelInit.focused = false;
    TagList->AddList({
        //new TTagLineScrollCaptionComment("U1/RAM/UEWG/", LabelInit),
        });
}
