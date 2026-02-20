#include "PageOperationFlags.h"
#include <FixedHeader.h>
#include "Router.h"
#include "TagLine.h"

TPageOperationFlags::TPageOperationFlags(std::string Name) : TPageSensors(Name) {
    TLabelInitStructure LabelInitH;
    LabelInitH.pOwner = Container;
    LabelInitH.caption = "Флаги работы";
    TFixedHeader* pHeader = new TFixedHeader(LabelInitH);
    delete Container->List[0];
    Container->List[0] = pHeader;
}

void TPageOperationFlags::fillPageContainer() {
    TagList->Clear();
    TLabelInitStructure LabelInit;
    LabelInit.style = LabelsStyle::WIDTH_FIXED;
    LabelInit.Rect = { 10, 10, 10, 80 };
    LabelInit.focused = false;
    TagList->AddList({
        new TTagLine("OutPolarity", "U1/RAM/flash_error/", LabelInit),
        new TTagLine("Ready", "U1/RAM/SyncFail/", LabelInit),
        new TTagLine("Run", "U1/RAM/PowerFail/", LabelInit),
        new TTagLine("Limit", "U1/RAM/PhaseOrderFail/", LabelInit)
        });
}