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
        new TTagLine("DI_RESET", "U1/RAM/DI_RESET/", LabelInit),
        new TTagLine("DI_MAIN_SW", "U1/RAM/DI_MAIN_SW/", LabelInit),
        new TTagLine("DI_START", "U1/RAM/DI_START/", LabelInit),
        new TTagLine("DI_STOP", "U1/RAM/DI_STOP/", LabelInit),
        new TTagLine("DI_FUSE", "U1/RAM/DI_FUSE/", LabelInit)
        });
}
