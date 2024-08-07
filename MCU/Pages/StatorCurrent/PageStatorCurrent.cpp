#include "PageStatorCurrent.h"
#include "TagLine.h"
#include "FixedHeader.h"

//Ток статора
TPageStatorCurrent::TPageStatorCurrent(std::string Name) : TPageBasicSettings(Name){
    TLabelInitStructure LabelInitH;
    LabelInitH.pOwner = Container;
    LabelInitH.caption = "Ток статора";
    TFixedHeader* pHeader = new TFixedHeader(LabelInitH);
    delete Container->List[0];
    Container->List[0] = pHeader;
}

void TPageStatorCurrent::fillPageContainer(void){
    TagList->Clear();
    TLabelInitStructure LabelInit;
    LabelInit.style = LabelsStyle::WIDTH_DINAMIC;
    LabelInit.Rect = {10, 10, 10, 10};
    LabelInit.focused = false;

    TagList->AddList({
        new TTagLine("IstStartTrig", "U1/RAM/IstStartTrig/", LabelInit),
        new TTagLine("IstOV", "U1/RAM/IstOV/", LabelInit),
        new TTagLine("Istat", "U1/RAM/Istat/", LabelInit),
        new TTagLine("Istat_max", "U1/RAM/Istat_max/", LabelInit),
        new TTagLine("IstStart", "U1/FLASH/IstStart/", LabelInit),
        new TTagLine("IstStop", "U1/FLASH/IstStop/", LabelInit),
        new TTagLine("IstExcEnable", "U1/FLASH/IstExcEnable/", LabelInit),
        new TTagLine("stIstOVFltEnable", "U1/FLASH/stIstOVFltEnable/", LabelInit),
        new TTagLine("Ti2tS", "U1/FLASH/Ti2tS/", LabelInit),
        new TTagLine("IstOVLFlt", "U1/FLASH/IstOVLFlt/", LabelInit),
        });
}
