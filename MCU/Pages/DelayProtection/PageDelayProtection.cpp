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
        new TTagLineScrollCaptionComment("U1/FLASH/TIloadAlarm/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/TIdcBusAlarm/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/TExitationLost/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/TIexcFlt/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/TOverheat/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/TOverheatLM19/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/TDRV_ERROR/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/TIloadMTZ/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/TIexcMTZ/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/TReversUdcBus/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/TFUAlarm/", LabelInit),
        });
}
