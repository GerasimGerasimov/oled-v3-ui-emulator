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
        new TTagLine("PWR1", "U1/RAM/PWR1/", LabelInit),
        new TTagLine("backup_error", "U1/RAM/backup_error/", LabelInit),
        new TTagLine("fram_error", "U1/RAM/fram_error/", LabelInit),
        new TTagLine("fram_bkp_error", "U1/RAM/fram_bkp_error/", LabelInit)
        });
}