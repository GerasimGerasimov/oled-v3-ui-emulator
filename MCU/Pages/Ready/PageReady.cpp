#include "PageReady.h"
#include "TagLineScrollCaptionComment.h"
#include <FixedHeader.h>

TPageReady::TPageReady(std::string Name) : TPageSensors(Name){
    TLabelInitStructure LabelInitH;
    LabelInitH.pOwner = Container;
    LabelInitH.caption = "Готовность";
    TFixedHeader* pHeader = new TFixedHeader(LabelInitH);
    delete Container->List[0];
    Container->List[0] = pHeader;
}

void TPageReady::fillPageContainer(){
    TagList->Clear();
    TLabelInitStructure LabelInit;
    LabelInit.style = LabelsStyle::WIDTH_FIXED;
    LabelInit.Rect = {10, 10, 10, 70};
    LabelInit.focused = false;
    TagList->AddList({
        new TTagLine("iReady", "U1/RAM/iReady/", LabelInit),
        new TTagLine("iPCSB_QF1", "U1/RAM/iPCSB_QF1/", LabelInit),
        new TTagLine("iCCSB_QF5", "U1/RAM/iCCSB_QF5/", LabelInit),
        new TTagLine("DExS_PWR_OK", "U1/RAM/DExS_PWR_OK/", LabelInit),
        new TTagLine("iSwState", "U1/RAM/iSwState/", LabelInit),
        new TTagLine("FAULT", "U1/RAM/FAULT/", LabelInit),
        new TTagLine("TestMode", "U1/RAM/TestMode/", LabelInit),
        });
}
