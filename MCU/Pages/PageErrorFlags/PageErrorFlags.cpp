#include "PageErrorFlags.h"
#include <FixedHeader.h>
#include "Router.h"
#include "TagLine.h"

TPageErrorFlags::TPageErrorFlags(std::string Name) : TPageSensors(Name) {
    TLabelInitStructure LabelInitH;
    LabelInitH.pOwner = Container;
    LabelInitH.caption = "Флаги готовности";
    TFixedHeader* pHeader = new TFixedHeader(LabelInitH);
    delete Container->List[0];
    Container->List[0] = pHeader;
}

void TPageErrorFlags::fillPageContainer() {
    TagList->Clear();
    TLabelInitStructure LabelInit;
    LabelInit.style = LabelsStyle::WIDTH_FIXED;
    LabelInit.Rect = { 10, 10, 10, 80 };
    LabelInit.focused = false;
    TagList->AddList({
        new TTagLine("UinLowFail", "U1/RAM/UinLowFail/", LabelInit),
        new TTagLine("MAIN_SW", "U1/RAM/DI_MAIN_SW/", LabelInit),
        new TTagLine("FUSE", "U1/RAM/DI_FUSE/", LabelInit)
        });
}