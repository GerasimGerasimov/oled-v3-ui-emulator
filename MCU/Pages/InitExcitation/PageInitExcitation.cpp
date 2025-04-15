#include "PageInitExcitation.h"
#include "TagLineScrollCaptionComment.h"
#include <FixedHeader.h>

TPageInitExcitation::TPageInitExcitation(std::string Name) : TPageBasicSettings(Name){
    TLabelInitStructure LabelInitH;
    LabelInitH.pOwner = Container;
    LabelInitH.caption = "Нач. возбуждение";
    TFixedHeader* pHeader = new TFixedHeader(LabelInitH);
    delete Container->List[0];
    Container->List[0] = pHeader;
}

void TPageInitExcitation::fillPageContainer(){
    TagList->Clear();
    TLabelInitStructure LabelInit;
    LabelInit.style = LabelsStyle::WIDTH_FIXED;
    LabelInit.Rect = {10, 10, 10, 70};
    LabelInit.focused = false;
    TagList->AddList({
        new TTagLineScrollCaptionComment("U1/FLASH/IexcTest/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/fIexcStart/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/dIexcOfUpStart/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/fIexcMax/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/UstNom/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/UstStart/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/FltUpVoltageTime/", LabelInit),
        });
}
