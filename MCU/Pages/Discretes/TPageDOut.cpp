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
    LabelInit.Rect = { 10, 10, 10, 70 };
    LabelInit.focused = false;
    TagList->AddList({
        new TTagLineScrollCaptionComment("U1/RAM/oCROWBAR_K1/", LabelInit),
        new TTagLineScrollCaptionComment("U1/RAM/oREADY_K2/", LabelInit),
        new TTagLineScrollCaptionComment("U1/RAM/oWARNING_K3/", LabelInit),
        new TTagLineScrollCaptionComment("U1/RAM/oFAULT_K4/", LabelInit),
        new TTagLineScrollCaptionComment("U1/RAM/oExcite_K5/", LabelInit),
        new TTagLineScrollCaptionComment("U1/RAM/oComplete_K6/", LabelInit),
        new TTagLineScrollCaptionComment("U1/RAM/oINSLFlt_K7/", LabelInit),
        new TTagLineScrollCaptionComment("U1/RAM/oReserve_K8/", LabelInit),
        new TTagLineScrollCaptionComment("U1/RAM/oStartExcite/", LabelInit),
        });
}
