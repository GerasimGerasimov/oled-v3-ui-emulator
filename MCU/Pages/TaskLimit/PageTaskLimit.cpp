#include "PageTaskLimit.h"
#include "TagLineVarSize.h"
#include <FixedHeader.h>

TPageTaskLimit::TPageTaskLimit(std::string Name) : TPageBasicSettings(Name){
    TLabelInitStructure LabelInitH;
    LabelInitH.pOwner = Container;
    LabelInitH.caption = "Огран. задания";
    TFixedHeader* pHeader = new TFixedHeader(LabelInitH);
    delete Container->List[0];
    Container->List[0] = pHeader;
}

void TPageTaskLimit::fillPageContainer(void){
    TagList->Clear();
    TLabelInitStructure LabelInit;
    LabelInit.style = LabelsStyle::WIDTH_DINAMIC;
    LabelInit.Rect = {10, 10, 10, 10};
    LabelInit.focused = false;
    TagList->AddList({
        new TTagLine("IExcMin", "U1/FLASH/IExcMin/", LabelInit),
        new TTagLine("IExcMax", "U1/FLASH/IExcMax/", LabelInit),
        new TTagLineVarSize("IExcManuMax", "U1/FLASH/IExcManuMax/", LabelInit, 0),
        new TTagLine("FLmax", "U1/FLASH/FLmax/", LabelInit),
        new TTagLine("FLmin", "U1/FLASH/FLmin/", LabelInit),
        new TTagLine("dIExcRef", "U1/FLASH/dIExcRef/", LabelInit),
        new TTagLine("dFiRef", "U1/FLASH/dFiRef/", LabelInit),
        });
}
