#include "TPageDOut.h"
#include "TagLineScrollCaptionComment.h"
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
    LabelInit.style = LabelsStyle::WIDTH_FIXED;
    LabelInit.Rect = { 10, 10, 10, 80 };
    LabelInit.focused = false;
    TagList->AddList({
        //new TTagLineScrollCaptionComment("U1/RAM/oCROWBAR_K1/", LabelInit),
        new TTagLine("DO_0", "U1/RAM/DO_0/", LabelInit),
        new TTagLine("PWR", "U1/RAM/DO_1_PWR/", LabelInit),
        new TTagLine("RUN", "U1/RAM/DO_2_RUN/", LabelInit),
        new TTagLine("STOP", "U1/RAM/DO_3_STOP/", LabelInit),
        new TTagLine("ALARM", "U1/RAM/DO_4_ALARM/", LabelInit)
        });
}
