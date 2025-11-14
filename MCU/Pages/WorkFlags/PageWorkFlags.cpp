#include "PageWorkFlags.h"
#include <FixedHeader.h>
#include "Router.h"
#include "TagLine.h"

TPageWorkFlags::TPageWorkFlags(std::string Name) : TPageSensors(Name) {
    TLabelInitStructure LabelInitH;
    LabelInitH.pOwner = Container;
    LabelInitH.caption = "Флаги работы";
    TFixedHeader* pHeader = new TFixedHeader(LabelInitH);
    delete Container->List[0];
    Container->List[0] = pHeader;
}

void TPageWorkFlags::fillPageContainer() {
    TagList->Clear();
    TLabelInitStructure LabelInit;
    LabelInit.style = LabelsStyle::WIDTH_FIXED;
    LabelInit.Rect = { 10, 10, 10, 80 };
    LabelInit.focused = false;
    TagList->AddList({
        new TTagLine("Ready", "U1/RAM/Ready/", LabelInit),
        new TTagLine("Run", "U1/RAM/Run/", LabelInit),
        new TTagLine("OutOk", "U1/RAM/OutOk/", LabelInit),
        new TTagLine("Fan1", "U1/RAM/Fan1/", LabelInit),
        new TTagLine("Fan2", "U1/RAM/Fan2/", LabelInit),
        new TTagLine("SoftStart", "U1/RAM/SoftStart/", LabelInit),
        new TTagLine("Ballast", "U1/RAM/Ballast/", LabelInit),
        new TTagLine("Discharge", "U1/RAM/Discharge/", LabelInit)
        });
}