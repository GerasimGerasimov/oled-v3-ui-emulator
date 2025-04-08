#include "PageDIn.h"
#include "TagLineScrollCaptionComment.h"
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
    LabelInit.style = LabelsStyle::WIDTH_FIXED;
    LabelInit.Rect = { 10, 10, 10, 70 };
    LabelInit.focused = false;
    TagList->AddList({
        new TTagLineScrollCaptionComment("U1/RAM/DI0_Start/", LabelInit),
        new TTagLineScrollCaptionComment("U1/RAM/DI1_Stop/", LabelInit),
        new TTagLineScrollCaptionComment("U1/RAM/DI2_Deblock/", LabelInit),
        new TTagLineScrollCaptionComment("U1/RAM/DI3_FanRdy/", LabelInit),
        new TTagLineScrollCaptionComment("U1/RAM/DI4_Door/", LabelInit),
        new TTagLineScrollCaptionComment("U1/RAM/DI5_Estop/", LabelInit),
        new TTagLineScrollCaptionComment("U1/RAM/DI7_U_DECR/", LabelInit),
        new TTagLineScrollCaptionComment("U1/RAM/DI8_U_INCR/", LabelInit),
        });
}
