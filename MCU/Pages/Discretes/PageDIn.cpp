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
        new TTagLine("START", "U1/RAM/DI_0_START/", LabelInit),
        new TTagLine("STOP", "U1/RAM/DI_1_STOP/", LabelInit),
        new TTagLine("DEBLOCK", "U1/RAM/DI_2_DEBLOCK/", LabelInit),
        new TTagLine("READY_SW", "U1/RAM/DI_3_READY_SW/", LabelInit),
        new TTagLine("DOOR_STATE", "U1/RAM/DI_4_DOOR_STATE/", LabelInit),
        new TTagLine("ESTOP", "U1/RAM/DI_5_ESTOP/", LabelInit),
        new TTagLine("PWR_CONT", "U1/RAM/DI_6_PWR_CONT/", LabelInit),
        new TTagLine("Ballast", "U1/RAM/DI_7_Ballast/", LabelInit)
        });
}
