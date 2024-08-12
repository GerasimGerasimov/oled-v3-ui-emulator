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
        //new TTagLine("UstLow", "U1/RAM/UstLow/", LabelInit),
        //new TTagLine("UstFail", "U1/RAM/UstFail/", LabelInit),
        //new TTagLine("Ustat", "U1/RAM/Ustat/", LabelInit),
        new TTagLine("stUstFltReadyEnable", "U1/FLASH/stUstFltReadyEnable/", LabelInit),
        new TTagLine("UstNom", "U1/FLASH/UstNom/", LabelInit),
        new TTagLine("UstLowReset", "U1/FLASH/UstLowReset/", LabelInit),
        new TTagLine("UstLowSet", "U1/FLASH/UstLowSet/", LabelInit),
        new TTagLine("UstFailReset", "U1/FLASH/UstFailReset/", LabelInit),
        new TTagLine("UstFailSet", "U1/FLASH/UstFailSet/", LabelInit),
        //new TTagLine("UstMax", "U1/FLASH/UstMax/", LabelInit),
        //new TTagLine("UstMaxTime", "U1/FLASH/UstMaxTime/", LabelInit),
        //new TTagLine("UsARV3", "U1/FLASH/UsARV3/", LabelInit),
        //new TTagLine("KUsARV3", "U1/FLASH/KUsARV3/", LabelInit),
        });
}
