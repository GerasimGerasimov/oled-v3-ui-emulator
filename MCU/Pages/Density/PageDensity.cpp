#include "PageDensity.h"
#include <FixedHeader.h>
#include "Router.h"
#include "TagLine.h"

TPageDensity::TPageDensity(std::string Name) : TPageSensors(Name) {
    TLabelInitStructure LabelInitH;
    LabelInitH.pOwner = Container;
    LabelInitH.caption = "Плотность";
    TFixedHeader* pHeader = new TFixedHeader(LabelInitH);
    delete Container->List[0];
    Container->List[0] = pHeader;
}

void TPageDensity::fillPageContainer() {
    TagList->Clear();
    TLabelInitStructure LabelInit;
    LabelInit.style = LabelsStyle::WIDTH_FIXED;
    LabelInit.Rect = { 10, 10, 10, 80 };
    LabelInit.focused = false;
    TagList->AddList({
        new TTagLine("Dref", "U1/RAM/Dref/", LabelInit),
        new TTagLine("S", "U1/RAM/S/", LabelInit)
        });
}
