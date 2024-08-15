#include "PageRotorProtection.h"
#include "TagLineScrollCaptionComment.h"
#include <FixedHeader.h>

TPageRotorProtection::TPageRotorProtection(std::string Name) : TPageBasicSettings(Name){
    TLabelInitStructure LabelInitH;
    LabelInitH.pOwner = Container;
    LabelInitH.caption = "Защиты ротора";
    TFixedHeader* pHeader = new TFixedHeader(LabelInitH);
    delete Container->List[0];
    Container->List[0] = pHeader;
}

void TPageRotorProtection::fillPageContainer(void){
    TagList->Clear();
    TLabelInitStructure LabelInit;
    LabelInit.style = LabelsStyle::WIDTH_FIXED;
    LabelInit.Rect = {10, 10, 10, 70};
    LabelInit.focused = false;
    TagList->AddList({
        new TTagLineScrollCaptionComment("U1/FLASH/IrMaxFlt/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/stFieldFltEnable/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/FieldFailTime/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/fIrFieldFail/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/Ti2tR/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/iIExci2tOvOnR/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/iIExci2tOvOffR/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/IExcI2tRef/", LabelInit),
        });
}
