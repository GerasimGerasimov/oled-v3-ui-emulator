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
    LabelInit.Rect = { 10, 10, 10, 80 };
    LabelInit.focused = false;
    TagList->AddList({
        new TTagLineScrollCaptionComment("U1/RAM/iReady/", LabelInit),
        new TTagLineScrollCaptionComment("U1/RAM/iTest/", LabelInit),
        new TTagLineScrollCaptionComment("U1/RAM/iReset/", LabelInit),
        new TTagLineScrollCaptionComment("U1/RAM/iSwState/", LabelInit),
        new TTagLineScrollCaptionComment("U1/RAM/iIRpP/", LabelInit),
        new TTagLineScrollCaptionComment("U1/RAM/iIRmM/", LabelInit),
        new TTagLineScrollCaptionComment("U1/RAM/iAuto/", LabelInit),
        new TTagLineScrollCaptionComment("U1/RAM/iEnergize/", LabelInit),
        new TTagLineScrollCaptionComment("U1/RAM/iBlanking/", LabelInit),
        new TTagLineScrollCaptionComment("U1/RAM/iSGFault/", LabelInit),
        new TTagLineScrollCaptionComment("U1/RAM/iPCSB_QF1/", LabelInit),
        new TTagLineScrollCaptionComment("U1/RAM/iCCSB_QF5/", LabelInit),
        new TTagLineScrollCaptionComment("U1/RAM/iLocalMode/", LabelInit),
        new TTagLineScrollCaptionComment("U1/RAM/iPB_Ready/", LabelInit),
        new TTagLineScrollCaptionComment("U1/RAM/iPB_Fault/", LabelInit),
        });
}
