#include "PageStatorVoltage.h"
#include "TagLineVarSize.h"
#include "TagLineScrollCaption.h"
#include "FixedHeader.h"

//Напряжение статора
TPageStatorVoltage::TPageStatorVoltage(std::string Name) : TPageBasicSettings(Name){
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
    LabelInit.Rect = {10, 10, 10, 70};
    LabelInit.focused = false;

    TagList->AddList({
        new TTagLineScrollCaption("stUstFltReadyEnable", "U1/FLASH/stUstFltReadyEnable/", LabelInit),
        new TTagLine("UstNom", "U1/FLASH/UstNom/", LabelInit),
        new TTagLineScrollCaption("UstLowReset", "U1/FLASH/UstLowReset/", LabelInit),
        new TTagLine("UstLowSet", "U1/FLASH/UstLowSet/", LabelInit),
        new TTagLineVarSize("UstFailReset", "U1/FLASH/UstFailReset/", LabelInit, 0),
        new TTagLineVarSize("UstFailSet", "U1/FLASH/UstFailSet/", LabelInit, 0)
        });
}
