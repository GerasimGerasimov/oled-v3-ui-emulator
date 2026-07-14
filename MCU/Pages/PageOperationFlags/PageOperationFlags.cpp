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
        new TTagLine("limit", "U1/RAM/limit/", LabelInit),
        new TTagLine("Ready", "U1/RAM/Ready/", LabelInit),
        new TTagLine("Run", "U1/RAM/Run/", LabelInit),
        new TTagLine("OutOk", "U1/RAM/OutOk/", LabelInit),
        new TTagLine("SoftStart", "U1/RAM/SoftStart/", LabelInit),
        new TTagLine("PWR1", "U1/RAM/PWR1/", LabelInit)
        });
}