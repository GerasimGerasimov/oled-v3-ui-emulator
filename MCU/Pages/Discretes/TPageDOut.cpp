#include "TPageDOut.h"
#include "TagLineScrollCaptionComment.h"
#include <FixedHeader.h>

TPageDOut::TPageDOut(std::string Name) : TPageInOut(Name){
    
    TLabelInitStructure LabelInit;
    LabelInit.pOwner = Container;
    LabelInit.caption = "���������� ������";
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
    LabelInit.style = LabelsStyle::WIDTH_FIXED;
    LabelInit.Rect = { 10, 10, 10, 70 };
    LabelInit.focused = false;
    TagList->AddList({
        new TTagLineScrollCaptionComment("U1/RAM/DO0_Alarm/", LabelInit),
        new TTagLineScrollCaptionComment("U1/RAM/DO1_Redy/", LabelInit),
        new TTagLineScrollCaptionComment("U1/RAM/DO4_Fan2/", LabelInit),
        new TTagLineScrollCaptionComment("U1/RAM/DO5_Run/", LabelInit),
        new TTagLineScrollCaptionComment("U1/RAM/DO6_Stop/", LabelInit),
        });
}
