#include "PageDebugInfo.h"
#include <FixedHeader.h>
#include "Router.h"
#include "TagLine.h"

TPageDebugInfo::TPageDebugInfo(std::string Name) : TPageSensors(Name) {
    TLabelInitStructure LabelInitH;
    LabelInitH.pOwner = Container;
    LabelInitH.caption = "Отладочная информ.";
    TFixedHeader* pHeader = new TFixedHeader(LabelInitH);
    delete Container->List[0];
    Container->List[0] = pHeader;
}

void TPageDebugInfo::fillPageContainer() {
    TagList->Clear();
    TLabelInitStructure LabelInit;
    LabelInit.style = LabelsStyle::WIDTH_FIXED;
    LabelInit.Rect = { 10, 10, 10, 80 };
    LabelInit.focused = false;
    TagList->AddList({
        new TTagLine("Fin", "U1/RAM/Fin/", LabelInit),
        new TTagLine("Iout_full", "U1/RAM/Iout_full/", LabelInit),
        new TTagLine("Alpha", "U1/RAM/Alpha/", LabelInit),
        new TTagLine("LinkState", "U1/RAM/LinkState/", LabelInit),
        new TTagLine("ControlCmd", "U1/RAM/ControlCmd/", LabelInit),
        new TTagLine("Ustat", "U1/RAM/Ustat/", LabelInit),
        new TTagLine("RawRef", "U1/RAM/RawRef/", LabelInit),
        new TTagLine("CI_IRef", "U1/RAM/CI_IRef/", LabelInit),
        new TTagLine("CI_URef", "U1/RAM/CI_URef/", LabelInit)
        });
}
