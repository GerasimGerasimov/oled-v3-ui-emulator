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
        new TTagLineScrollCaptionComment("U1/RAM/iStartBtn/", LabelInit),
        new TTagLineScrollCaptionComment("U1/RAM/iWindDry/", LabelInit),
        new TTagLineScrollCaptionComment("U1/RAM/iOVH/", LabelInit),
        new TTagLineScrollCaptionComment("U1/RAM/iMPSState/", LabelInit),
        new TTagLineScrollCaptionComment("U1/RAM/iSPPExFrce/", LabelInit),
        new TTagLineScrollCaptionComment("U1/RAM/iSPPExEnbl/", LabelInit),
        new TTagLineScrollCaptionComment("U1/RAM/iRMSState/", LabelInit),
        new TTagLineScrollCaptionComment("U1/RAM/iMMSState/", LabelInit),
        new TTagLineScrollCaptionComment("U1/RAM/iAuto/", LabelInit),
        new TTagLineScrollCaptionComment("U1/RAM/iIRm-/", LabelInit),
        new TTagLineScrollCaptionComment("U1/RAM/iIRp+/", LabelInit),
        new TTagLineScrollCaptionComment("U1/RAM/iReset/", LabelInit),
        new TTagLineScrollCaptionComment("U1/RAM/iTest/", LabelInit),
        new TTagLineScrollCaptionComment("U1/RAM/iReady/", LabelInit),
        });
}
