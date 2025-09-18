#include "PageAdditionalData.h"
#include <FixedHeader.h>
#include "Router.h"
#include "TagLine.h"

TPageAdditionalData::TPageAdditionalData(std::string Name) : TPageSensors(Name) {
    TLabelInitStructure LabelInitH;
    LabelInitH.pOwner = Container;
    LabelInitH.caption = "Дополн. данные";
    TFixedHeader* pHeader = new TFixedHeader(LabelInitH);
    delete Container->List[0];
    Container->List[0] = pHeader;
}

void TPageAdditionalData::fillPageContainer() {
    TagList->Clear();
    TLabelInitStructure LabelInit;
    LabelInit.style = LabelsStyle::WIDTH_FIXED;
    LabelInit.Rect = { 10, 10, 10, 80 };
    LabelInit.focused = false;
    TagList->AddList({
        new TTagLine("Uin", "U1/RAM/Uin/", LabelInit),
        new TTagLine("Alpha", "U1/RAM/Alpha/", LabelInit),
        new TTagLine("Fin", "U1/RAM/Fin/", LabelInit)
        });
}
