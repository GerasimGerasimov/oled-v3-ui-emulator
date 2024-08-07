#include "PageSliding.h"
#include "TagLine.h"
#include "FixedHeader.h"

//Скольжение
TPageSliding::TPageSliding(std::string Name) : TPageSensors(Name){
    TLabelInitStructure LabelInitH;
    LabelInitH.pOwner = Container;
    LabelInitH.caption = "Скольжение";
    TFixedHeader* pHeader = new TFixedHeader(LabelInitH);
    delete Container->List[0];
    Container->List[0] = pHeader;
}

void TPageSliding::fillPageContainer(void){
    TagList->Clear();
    TLabelInitStructure LabelInit;
    LabelInit.style = LabelsStyle::WIDTH_DINAMIC;
    LabelInit.Rect = {10, 10, 10, 10};
    LabelInit.focused = false;

    TagList->AddList({
        new TTagLine("cfi_enable", "U1/RAM/cfi_enable/", LabelInit),
        new TTagLine("cfu_enable", "U1/RAM/cfu_enable/", LabelInit),
        new TTagLine("SlideFreqRealay", "U1/RAM/SlideFreqRealay/", LabelInit),
        new TTagLine("FS+", "U1/RAM/FS+/", LabelInit),
        new TTagLine("FS-", "U1/RAM/FS-/", LabelInit),
        new TTagLine("HS_freq_passed", "U1/RAM/HS_freq_passed/", LabelInit),
        new TTagLine("SlideCirctErr", "U1/RAM/SlideCirctErr/", LabelInit),
        new TTagLine("SlideFreg", "U1/RAM/SlideFreg/", LabelInit),
        new TTagLine("ExcEnableFreq", "U1/FLASH/ExcEnableFreq/", LabelInit),
        new TTagLine("HsFreq", "U1/FLASH/HsFreq/", LabelInit),
        new TTagLine("HsTime", "U1/FLASH/HsTime/", LabelInit),
        new TTagLine("FSAsyncTime", "U1/FLASH/FSAsyncTime/", LabelInit),
        });
}