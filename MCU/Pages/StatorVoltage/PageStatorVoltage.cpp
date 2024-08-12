#include "PageStatorVoltage.h"
#include "TagLine.h"
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
    LabelInit.style = LabelsStyle::WIDTH_DINAMIC;
    LabelInit.Rect = {10, 10, 10, 10};
    LabelInit.focused = false;

    TagList->AddList({
        new TTagLine("stUstFltReadyEnable", "U1/FLASH/stUstFltReadyEnable/", LabelInit),
        new TTagLine("UstNom", "U1/FLASH/UstNom/", LabelInit),
        new TTagLine("UstLowReset", "U1/FLASH/UstLowReset/", LabelInit),
        new TTagLine("UstLowSet", "U1/FLASH/UstLowSet/", LabelInit),
        new TTagLine("UstFailReset", "U1/FLASH/UstFailReset/", LabelInit),
        new TTagLine("UstFailSet", "U1/FLASH/UstFailSet/", LabelInit),
        });
}
