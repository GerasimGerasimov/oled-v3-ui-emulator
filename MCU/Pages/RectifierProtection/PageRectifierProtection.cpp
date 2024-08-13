#include "PageRectifierProtection.h"
#include "TagLineScrollCaption.h"
#include <FixedHeader.h>

TPageRectifierProtection::TPageRectifierProtection(std::string Name) : TPageBasicSettings(Name){
    TLabelInitStructure LabelInitH;
    LabelInitH.pOwner = Container;
    LabelInitH.caption = "Защиты выпрямителя";
    TFixedHeader* pHeader = new TFixedHeader(LabelInitH);
    delete Container->List[0];
    Container->List[0] = pHeader;
}

void TPageRectifierProtection::fillPageContainer(void){
    TagList->Clear();
    TLabelInitStructure LabelInit;
    LabelInit.style = LabelsStyle::WIDTH_FIXED;
    LabelInit.Rect = {10, 10, 10, 70};
    LabelInit.focused = false;
    TagList->AddList({
        new TTagLine("IttMaxFlt", "U1/FLASH/IttMaxFlt/", LabelInit),
        new TTagLineScrollCaption("fIttAsymPrc", "U1/FLASH/fIttAsymPrc/", LabelInit),
        new TTagLine("fIttAsymT", "U1/FLASH/fIttAsymTime/", LabelInit),
    });
}
