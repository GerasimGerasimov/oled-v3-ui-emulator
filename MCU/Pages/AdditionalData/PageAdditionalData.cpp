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
        new TTagLine("Ua", "U1/RAM/Ua/", LabelInit),
        new TTagLine("Ub", "U1/RAM/Ub/", LabelInit),
        new TTagLine("Uc", "U1/RAM/Uc/", LabelInit),
        new TTagLine("Iin", "U1/RAM/Iin/", LabelInit),
        new TTagLine("Ia", "U1/RAM/Ia/", LabelInit),
        new TTagLine("Ib", "U1/RAM/Ib/", LabelInit),
        new TTagLine("Ic", "U1/RAM/Ic/", LabelInit),
        new TTagLine("UoutCur", "U1/RAM/UoutCur/", LabelInit),
        new TTagLine("IoutCur", "U1/RAM/IoutCur/", LabelInit),
        new TTagLine("Tradiator1", "U1/RAM/Tradiator1/", LabelInit),
        new TTagLine("Tradiator2", "U1/RAM/Tradiator2/", LabelInit),
        new TTagLine("Tcabinet", "U1/RAM/Tcabinet/", LabelInit),
        new TTagLine("Alpha", "U1/RAM/Alpha/", LabelInit),
        new TTagLine("Fin", "U1/RAM/Fin/", LabelInit),
        new TTagLine("Td_com", "U1/RAM/Td_com/", LabelInit),
        });
}
