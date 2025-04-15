#include "PageRegulatorKoeff.h"
#include "TagLineScrollCaptionComment.h"
#include <FixedHeader.h>

TPageRegulatorKoeff::TPageRegulatorKoeff(std::string Name) : TPageBasicSettings(Name){
    TLabelInitStructure LabelInitH;
    LabelInitH.pOwner = Container;
    LabelInitH.caption = "Коэфф. регулятора";
    TFixedHeader* pHeader = new TFixedHeader(LabelInitH);
    delete Container->List[0];
    Container->List[0] = pHeader;
}

void TPageRegulatorKoeff::fillPageContainer(){
    TagList->Clear();
    TLabelInitStructure LabelInit;
    LabelInit.style = LabelsStyle::WIDTH_FIXED;
    LabelInit.Rect = {10, 10, 10, 70};
    LabelInit.focused = false;
    TagList->AddList({
        new TTagLineScrollCaptionComment("U1/FLASH/KUst/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/KIexc/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/Ti/", LabelInit),
        //new TTagLineScrollCaptionComment("U1/CD/fUstat/", LabelInit),
        //new TTagLineScrollCaptionComment("U1/CD/TfIload/", LabelInit),
        //new TTagLineScrollCaptionComment("U1/CD/fPhi/", LabelInit),
        });
}
