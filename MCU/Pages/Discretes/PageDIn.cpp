#include "PageDIn.h"
#include "TagLine.h"
#include <FixedHeader.h>

TPageDIn::TPageDIn(std::string Name) : TPageInOut(Name)
{
    TLabelInitStructure LabelInit;
    LabelInit.pOwner = Container;
    LabelInit.caption = "Дискретные входы";
    TFixedHeader* pHeader = new TFixedHeader(LabelInit);
    Container->Add(pHeader);
    TagList->ElementRect = { 0, 0,
                            (u16)(VIEW_PORT_MAX_HEIGHT - pHeader->getHeight() - 1),
                            VIEW_PORT_MAX_WIDTH };
    Container->Add(TagList);
}

void TPageDIn::fillPageContainer()
{
    TagList->Clear();
    TLabelInitStructure LabelInit;
    LabelInit.style = LabelsStyle::WIDTH_DINAMIC;
    LabelInit.Rect = { 10, 10, 10, 10 };
    LabelInit.focused = false;
    TagList->AddList({
        new TTagLine("iStartBtn", "U1/RAM/iStartBtn/", LabelInit),
        new TTagLine("iWindDry", "U1/RAM/iWindDry/", LabelInit),
        new TTagLine("iOVH", "U1/RAM/iOVH/", LabelInit),
        new TTagLine("iMPSState", "U1/RAM/iMPSState/", LabelInit),
        new TTagLine("iSPPExFrce", "U1/RAM/iSPPExFrce/", LabelInit),
        new TTagLine("iSPPExEnbl", "U1/RAM/iSPPExEnbl/", LabelInit),
        new TTagLine("iRMSState", "U1/RAM/iRMSState/", LabelInit),
        new TTagLine("iMMSState", "U1/RAM/iMMSState/", LabelInit),
        new TTagLine("iAuto", "U1/RAM/iAuto/", LabelInit),
        new TTagLine("iIRm-", "U1/RAM/iIRm-/", LabelInit),
        new TTagLine("iIRp+", "U1/RAM/iIRp+/", LabelInit),
        new TTagLine("iReset", "U1/RAM/iReset/", LabelInit),
        new TTagLine("iTest", "U1/RAM/iTest/", LabelInit),
        new TTagLine("iReady", "U1/RAM/iReady/", LabelInit),
        });
}
