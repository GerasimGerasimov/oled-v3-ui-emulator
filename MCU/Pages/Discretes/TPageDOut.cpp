#include "TPageDOut.h"
#include "TagLineVarSize.h"
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
    LabelInit.style = LabelsStyle::WIDTH_DINAMIC;
    LabelInit.Rect = { 10, 10, 10, 10 };
    LabelInit.focused = false;
    TagList->AddList({
        new TTagLine("oBreakOff", "U1/RAM/oBreakOff/", LabelInit),
        new TTagLine("oLatch", "U1/RAM/oLatch/", LabelInit),
        new TTagLine("oFAN_K8", "U1/RAM/oFAN_K8/", LabelInit),
        new TTagLine("oSPP_K7", "U1/RAM/oSPP_K7/", LabelInit),
        new TTagLine("oUSER_K6", "U1/RAM/oUSER_K6/", LabelInit),
        new TTagLine("oMSS_K5", "U1/RAM/oMSS_K5/", LabelInit),
        new TTagLine("oFAULT_K4", "U1/RAM/oFAULT_K4/", LabelInit),
        new TTagLineVarSize("oWARNING_K3", "U1/RAM/oWARNING_K3/", LabelInit, 0),
        new TTagLineVarSize("oREADY_K2", "U1/RAM/oREADY_K2/", LabelInit, 0),
        new TTagLineVarSize("oCROWBAR_K1", "U1/RAM/oCROWBAR_K1/", LabelInit, 0),
        });
    dynamic_cast<TTagLineVarSize*>(TagList->List[8])->setGap(25);//oREADY_K2
}
