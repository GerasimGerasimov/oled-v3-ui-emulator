#include "PageReactPowerLimit.h"
#include "TagLine.h"
#include <FixedHeader.h>

TPageReactPowerLimit::TPageReactPowerLimit(std::string Name) : TPageBasicSettings(Name){
    TLabelInitStructure LabelInitH;
    LabelInitH.pOwner = Container;
    LabelInitH.caption = "Огран. реакт. мощ.";
    TFixedHeader* pHeader = new TFixedHeader(LabelInitH);
    delete Container->List[0];
    Container->List[0] = pHeader;
}

void TPageReactPowerLimit::fillPageContainer(void){
    TagList->Clear();
    TLabelInitStructure LabelInit;
    LabelInit.style = LabelsStyle::WIDTH_DINAMIC;
    LabelInit.Rect = {10, 10, 10, 10};
    LabelInit.focused = false;
    TagList->AddList({
        new TTagLine("Pnom", "U1/FLASH/Pnom/", LabelInit),
        new TTagLine("QminP0", "U1/FLASH/QminP0/", LabelInit),
        new TTagLine("QminP1", "U1/FLASH/QminP1/", LabelInit),
        new TTagLine("dQmin", "U1/FLASH/dQmin/", LabelInit),
        new TTagLine("QmaxP0", "U1/FLASH/QmaxP0/", LabelInit),
        new TTagLine("QmaxP1", "U1/FLASH/QmaxP1/", LabelInit),
        });
}
