#include "PageStatorVoltage.h"
#include "TagLineScrollCaptionComment.h"
#include "FixedHeader.h"

//Напряжение статора
TPageStatorVoltage::TPageStatorVoltage(std::string Name) : TPageControlSettings(Name){
    TLabelInitStructure LabelInitH;
    LabelInitH.pOwner = Container;
    LabelInitH.caption = "Напряжение статора";
    TFixedHeader* pHeader = new TFixedHeader(LabelInitH);
    delete Container->List[0];
    Container->List[0] = pHeader;
}

void TPageStatorVoltage::fillPageContainer(void){
    TagList->Clear();
    TLabelInitStructure LabelInit;
    LabelInit.style = LabelsStyle::WIDTH_FIXED;
    LabelInit.Rect = {10, 10, 10, 80};
    LabelInit.focused = false;

    TagList->AddList({
        new TTagLineScrollCaptionComment("U1/RAM/Ustat/", LabelInit),
        new TTagLineScrollCaptionComment("U1/RAM/UstLow/", LabelInit),
        new TTagLineScrollCaption("Min уровень напряжения статора", "U1/RAM/UstFail/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/stUstFltReadyEnable/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/UstNom/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/UstLowReset/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/UstLowSet/", LabelInit),
        new TTagLineScrollCaption("Min уровень напряжения статора", "U1/FLASH/UstFailReset/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/UstFailSet/", LabelInit),
        new TTagLineScrollCaption("Max напряжение статора", "U1/FLASH/UstMax/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/UstMaxTime/", LabelInit)
        });


}
