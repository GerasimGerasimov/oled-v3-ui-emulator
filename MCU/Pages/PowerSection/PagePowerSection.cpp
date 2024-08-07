#include "PagePowerSection.h"
#include "TagLine.h"
#include "FixedHeader.h"

TPagePowerSection::TPagePowerSection(std::string Name) : TPageBasicSettings(Name){
    TLabelInitStructure LabelInitH;
    LabelInitH.pOwner = Container;
    LabelInitH.caption = "Силовая часть";
    TFixedHeader* pHeader = new TFixedHeader(LabelInitH);
    delete Container->List[0];
    Container->List[0] = pHeader;
}

void TPagePowerSection::fillPageContainer(void){
    TagList->Clear();
    TLabelInitStructure LabelInit;
    LabelInit.style = LabelsStyle::WIDTH_DINAMIC;
    LabelInit.Rect = {10, 10, 10, 10};
    LabelInit.focused = false;

    TagList->AddList({
        new TTagLine("ThyCtrlFault", "U1/RAM/ThyCtrlFault/", LabelInit),
        new TTagLine("stThyFltEnable", "U1/FLASH/stThyFltEnable/", LabelInit),
        new TTagLine("ThyCtrlFltTime", "U1/FLASH/ThyCtrlFltTime/", LabelInit),
        new TTagLine("IExcRef", "U1/FLASH/IExcRef/", LabelInit),

        new TTagLine("IExcTst", "U1/FLASH/IExcTst/", LabelInit),
        new TTagLine("IExcForce", "U1/FLASH/IExcForce/", LabelInit),
        new TTagLine("StartForceTime", "U1/FLASH/StartForceTime/", LabelInit),
        new TTagLine("TestTime", "U1/FLASH/TestTime/", LabelInit),
        new TTagLine("stDualPowerEnable", "U1/FLASH/stDualPowerEnable/", LabelInit),
        new TTagLine("DualPower", "U1/RAM/DualPower/", LabelInit),
        });
}
