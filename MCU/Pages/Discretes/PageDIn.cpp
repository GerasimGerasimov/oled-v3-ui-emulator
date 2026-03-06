#include "PageDIn.h"
#include "TagLineScrollCaptionComment.h"
#include <FixedHeader.h>
#include "TagLine.h"

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
    LabelInit.Rect = { 10, 10, 10, 80 };
    LabelInit.focused = false;
    TagList->AddList({
        new TTagLine("DEBLOCK", "U1/RAM/DI0_DEBLOCK/", LabelInit),
        new TTagLine("DIR_MODE", "U1/RAM/DI1_DIR_MODE/", LabelInit),
        new TTagLine("STAB_MODE", "U1/RAM/DI2_STAB_MODE/", LabelInit),
        new TTagLine("REF_PLUS", "U1/RAM/DI3_REF_PLUS/", LabelInit),
        new TTagLine("REF_MINUS", "U1/RAM/DI4_REF_MINUS/", LabelInit),
        new TTagLine("ON", "U1/RAM/DI5_ON/", LabelInit),
        new TTagLine("OVERHEAT_AVERS", "U1/RAM/DI6_OVERHEAT_AVERS/", LabelInit),
        new TTagLine("OVERHEAT_REVERS", "U1/RAM/DI7_OVERHEAT_REVERS/", LabelInit),
        new TTagLine("OVERHEAT_COOLIANT", "U1/RAM/DI8_OVERHEAT_COOLIANT/", LabelInit),
        new TTagLine("PWR_STATE", "U1/RAM/DI9_PWR_STATE/", LabelInit),
        new TTagLine("LOW_PRESSURE", "U1/RAM/DI10_LOW_PRESSURE/", LabelInit),
        new TTagLine("HI_PRESSURE", "U1/RAM/DI11_HI_PRESSURE/", LabelInit),
        new TTagLine("ESTOP", "U1/RAM/DI13_ESTOP/", LabelInit)
        });
}
