#include "PageDelayProtection.h"
#include "TagLineScrollCaptionComment.h"
#include <FixedHeader.h>

TPageDelayProtection::TPageDelayProtection(std::string Name) : TPageBasicSettings(Name){
    TLabelInitStructure LabelInitH;
    LabelInitH.pOwner = Container;
    LabelInitH.caption = "Задержки защит";
    TFixedHeader* pHeader = new TFixedHeader(LabelInitH);
    delete Container->List[0];
    Container->List[0] = pHeader;
}

void TPageDelayProtection::fillPageContainer(void){
    TagList->Clear();
    TLabelInitStructure LabelInit;
    LabelInit.style = LabelsStyle::WIDTH_FIXED;
    LabelInit.Rect = {10, 10, 10, 70};
    LabelInit.focused = false;
    TagList->AddList({
        new TTagLineScrollCaptionComment("U1/FLASH/TKM1/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/TKM2/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/TIloadOverload/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/TIdcShortCircuit/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/TExitationLost/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/TIexcFlt/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/TOverheat/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/TExtOverHeat/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/TDRV_ERROR/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/TIloadShortCircuit/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/TIexcShortCircuit/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/TReversUdcBus/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/TFuseAlarm/", LabelInit),
        });
}
