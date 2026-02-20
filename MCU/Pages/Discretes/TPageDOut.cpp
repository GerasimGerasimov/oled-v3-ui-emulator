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
        new TTagLine("READY", "U1/RAM/DO0_READY/", LabelInit),
        new TTagLine("STOP", "U1/RAM/DO1_STOP/", LabelInit),
        new TTagLine("RUN", "U1/RAM/DO2_RUN/", LabelInit),
        new TTagLine("REVERSE", "U1/RAM/DO3_REVERSE/", LabelInit),
        new TTagLine("AUTO", "U1/RAM/DO4_AUTO/", LabelInit),
        new TTagLine("COOLER_OK", "U1/RAM/DO5_COOLER_OK/", LabelInit),
        new TTagLine("ORDER_FAIL", "U1/RAM/DO6_ORDER_FAIL/", LabelInit),
        new TTagLine("OVERLOAD", "U1/RAM/DO7_OVERLOAD/", LabelInit),
        new TTagLine("OVERHEAT", "U1/RAM/DO8_OVERHEAT/", LabelInit),
        new TTagLine("ALARM", "U1/RAM/DO9_ALARM/", LabelInit)
        });
}
