#include "PageGeneratorMode.h"
#include "TagLine.h"
#include "FixedHeader.h"

TPageGeneratorMode::TPageGeneratorMode(std::string Name) : TPageBasicSettings(Name){
    TLabelInitStructure LabelInitH;
    LabelInitH.pOwner = Container;
    LabelInitH.caption = "Генераторный режим";
    TFixedHeader* pHeader = new TFixedHeader(LabelInitH);
    delete Container->List[0];
    Container->List[0] = pHeader;
}

void TPageGeneratorMode::fillPageContainer(void){
    TagList->Clear();
    TLabelInitStructure LabelInit;
    LabelInit.style = LabelsStyle::WIDTH_DINAMIC;
    LabelInit.Rect = {10, 10, 10, 10};
    LabelInit.focused = false;

    TagList->AddList({
        new TTagLine("GMP", "U1/RAM/GMP/", LabelInit),
        new TTagLine("stGenMdFltEnable", "U1/FLASH/stGenMdFltEnable/", LabelInit),
        new TTagLine("stGenModeSelect", "U1/FLASH/stGenModeSelect/", LabelInit),
        new TTagLine("GMPU", "U1/FLASH/GMPU/", LabelInit),
        new TTagLine("GMPUFltTime", "U1/FLASH/GMPUFltTime/", LabelInit),
        });
}
