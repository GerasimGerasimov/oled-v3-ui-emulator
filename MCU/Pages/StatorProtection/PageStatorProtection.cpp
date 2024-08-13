#include "PageStatorProtection.h"
#include "TagLineVarSize.h"
#include <FixedHeader.h>

TPageStatorProtection::TPageStatorProtection(std::string Name) : TPageBasicSettings(Name){
    TLabelInitStructure LabelInitH;
    LabelInitH.pOwner = Container;
    LabelInitH.caption = "Защиты статора";
    TFixedHeader* pHeader = new TFixedHeader(LabelInitH);
    delete Container->List[0];
    Container->List[0] = pHeader;
}

void TPageStatorProtection::fillPageContainer(void){
    TagList->Clear();
    TLabelInitStructure LabelInit;
    LabelInit.style = LabelsStyle::WIDTH_DINAMIC;
    LabelInit.Rect = {10, 10, 10, 10};
    LabelInit.focused = false;
    TagList->AddList({
        new TTagLine("FSAsyncT", "U1/FLASH/FSAsyncTime/", LabelInit),
        new TTagLine("UstMax", "U1/FLASH/UstMax/", LabelInit),
        new TTagLine("UstMaxT", "U1/FLASH/UstMaxTime/", LabelInit),
        new TTagLineVarSize("stFreqDwnFltEn", "U1/FLASH/stFreqDwnFltEnable/", LabelInit, 0),
        new TTagLine("FreqMinFlt", "U1/FLASH/FreqMinFlt/", LabelInit),
        new TTagLine("FreqMinFltT", "U1/FLASH/FreqMinFltTime/", LabelInit),
        new TTagLine("Ti2tS", "U1/FLASH/Ti2tS/", LabelInit),
        new TTagLine("IstOVLFlt", "U1/FLASH/IstOVLFlt/", LabelInit),
        });
}
