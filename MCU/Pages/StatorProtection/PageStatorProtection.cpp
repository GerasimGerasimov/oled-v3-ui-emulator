#include "PageStatorProtection.h"
#include "TagLineScrollCaptionComment.h"
#include <FixedHeader.h>

TPageStatorProtection::TPageStatorProtection(std::string Name) : TPageBasicSettings(Name){
    TLabelInitStructure LabelInitH;
    LabelInitH.pOwner = Container;
    LabelInitH.caption = "Защиты статора";
    TFixedHeader* pHeader = new TFixedHeader(LabelInitH);
    delete Container->List[0];
    Container->List[0] = pHeader;
}

void TPageStatorProtection::fillPageContainer(void){
    TagList->Clear();
    TLabelInitStructure LabelInit;
    LabelInit.style = LabelsStyle::WIDTH_FIXED;
    LabelInit.Rect = {10, 10, 10, 70};
    LabelInit.focused = false;
    TagList->AddList({
        new TTagLineScrollCaptionComment("U1/FLASH/FSAsyncTime/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/UstMax/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/UstMaxTime/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/stFreqDwnFltEnable/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/FreqMinFlt/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/FreqMinFltTime/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/Ti2tS/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/IstOVLFlt/", LabelInit),
        });
}
