#include "PageCurrentProtection.h"
#include "TagLine.h"
#include "FixedHeader.h"

//Токовые защиты возбудителя
TPageCurrentProtection::TPageCurrentProtection(std::string Name) : TPageBasicSettings(Name){
    TLabelInitStructure LabelInitH;
    LabelInitH.pOwner = Container;
    LabelInitH.caption = "Токовые защиты";
    TFixedHeader* pHeader = new TFixedHeader(LabelInitH);
    delete Container->List[0];
    Container->List[0] = pHeader;
}

void TPageCurrentProtection::fillPageContainer(void){
    TagList->Clear();
    TLabelInitStructure LabelInit;
    LabelInit.style = LabelsStyle::WIDTH_DINAMIC;
    LabelInit.Rect = {10, 10, 10, 10};
    LabelInit.focused = false;

    TagList->AddList({
        new TTagLine("IExcMaxFlt", "U1/RAM/IExcMaxFlt/", LabelInit),
        new TTagLine("IttMaxFlt", "U1/RAM/IttMaxFlt/", LabelInit),
        new TTagLine("IttAsymFlt", "U1/RAM/IttAsymFlt/", LabelInit),
        new TTagLine("IrMaxFlt", "U1/FLASH/IrMaxFlt/", LabelInit),
        new TTagLine("IttMaxFlt", "U1/FLASH/IttMaxFlt/", LabelInit),
        new TTagLine("fIttAsymPrc", "U1/FLASH/fIttAsymPrc/", LabelInit),
        new TTagLine("fIttAsymTime", "U1/FLASH/fIttAsymTime/", LabelInit),
        });
}
