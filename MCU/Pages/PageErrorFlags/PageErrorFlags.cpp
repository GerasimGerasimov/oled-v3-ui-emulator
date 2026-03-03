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
        new TTagLine("flash_error", "U1/RAM/flash_error/", LabelInit),
        new TTagLine("SyncFail", "U1/RAM/SyncFail/", LabelInit),
        new TTagLine("PowerFail", "U1/RAM/PowerFail/", LabelInit),
        new TTagLine("PhaseOrderFail", "U1/RAM/PhaseOrderFail/", LabelInit),
        new TTagLine("LnkMngrFail", "U1/RAM/LnkMngrFail/", LabelInit),
        new TTagLine("FlowFail", "U1/RAM/FlowFail/", LabelInit),
        new TTagLine("OverheatFail", "U1/RAM/OverheatFail/", LabelInit),
        new TTagLine("PressureFail", "U1/RAM/PressureFail/", LabelInit),
        new TTagLine("PwrSwitchFail", "U1/RAM/PwrSwitchFail/", LabelInit)
        });
}