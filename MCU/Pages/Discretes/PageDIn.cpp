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
        new TTagLine("iINSLEXC", "U1/RAM/iINSLEXC/", LabelInit),
        new TTagLine("iQ2EXC", "U1/RAM/iQ2EXC/", LabelInit),
        new TTagLine("iKM2EXC", "U1/RAM/iKM2EXC/", LabelInit),
        new TTagLine("iKM1ANC", "U1/RAM/iKM1ANC/", LabelInit),
        new TTagLine("iQ1", "U1/RAM/iQ1/", LabelInit),
        new TTagLine("iReset", "U1/RAM/iReset/", LabelInit),
        new TTagLine("iEnable", "U1/RAM/iEnable/", LabelInit),
        new TTagLine("iOVH", "U1/RAM/iOVH/", LabelInit),
        });
}
