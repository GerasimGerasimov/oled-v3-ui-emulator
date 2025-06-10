#include "PagePowerSupply.h"
#include "PageSensors.h"
#include "Router.h"
#include "TagLine.h"
#include <IniResources.h>
#include <FixedHeader.h>

TPagePowerSupply::TPagePowerSupply(std::string Name) : TPageSensors(Name) {
    TLabelInitStructure LabelInitH;
    LabelInitH.pOwner = Container;
    LabelInitH.caption = "Питающая сеть";
    TFixedHeader* pHeader = new TFixedHeader(LabelInitH);
    delete Container->List[0];
    Container->List[0] = pHeader;
}

void TPagePowerSupply::fillPageContainer() {
    TagList->Clear();
    TLabelInitStructure LabelInit;
    LabelInit.style = LabelsStyle::WIDTH_FIXED;
    LabelInit.Rect = { 10, 10, 10, 80 };
    LabelInit.focused = false;
    TagList->AddList({
        new TTagLine("FreqRect", "U1/RAM/FreqRect/", LabelInit),
        new TTagLine("Vab_sync", "U1/RAM/Vab_sync/", LabelInit),
        new TTagLine("Vbc_sync", "U1/RAM/Vbc_sync/", LabelInit),
        new TTagLine("Vca_sync", "U1/RAM/Vca_sync/", LabelInit),
        new TTagLine("IttA", "U1/RAM/IttA/", LabelInit),
        new TTagLine("IttB", "U1/RAM/IttB/", LabelInit),
        new TTagLine("IttC", "U1/RAM/IttC/", LabelInit),
        //new TTagLineScrollCaptionComment("U1/RAM/UEWG/", LabelInit),
        });
}
