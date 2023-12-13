#include "TPageDOut.h"
#include "TagLine.h"
#include <FixedHeader.h>

TPageDOut::TPageDOut(std::string Name) : TPageInOut(Name){
    
    TLabelInitStructure LabelInit;
    LabelInit.pOwner = Container;
    LabelInit.caption = "Дискретные выходы";
    TFixedHeader* pHeader = new TFixedHeader(LabelInit);
    Container->Add(pHeader);
    TagList->ElementRect = { 0, 0,
                        (u16)(VIEW_PORT_MAX_HEIGHT - pHeader->getHeight() - 1),
                        VIEW_PORT_MAX_WIDTH };
    Container->Add(TagList);
}

void TPageDOut::fillPageContainer()
{
    TagList->Clear();
    TLabelInitStructure LabelInit;
    LabelInit.style = LabelsStyle::WIDTH_DINAMIC;
    LabelInit.Rect = { 10, 10, 10, 10 };
    LabelInit.focused = false;
    TagList->AddList({
        new TTagLine("oQ1EN", "U1/RAM/oQ1EN/", LabelInit),
        new TTagLine("oKM2EXC", "U1/RAM/oKM2EXC/", LabelInit),
        new TTagLine("oKM1ANC", "U1/RAM/oKM1ANC/", LabelInit),
        new TTagLine("oFault", "U1/RAM/oFault/", LabelInit),
        });
}
