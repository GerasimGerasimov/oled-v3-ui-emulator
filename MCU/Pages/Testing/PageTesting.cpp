#include "PageTesting.h"
#include "TagLineScrollCaptionComment.h"
#include "FixedHeader.h"

//Опробование
TPageTesting::TPageTesting(std::string Name) : TPageControlSettings(Name){
    TLabelInitStructure LabelInitH;
    LabelInitH.pOwner = Container;
    LabelInitH.caption = "Опробование";
    TFixedHeader* pHeader = new TFixedHeader(LabelInitH);
    delete Container->List[0];
    Container->List[0] = pHeader;
}

void TPageTesting::fillPageContainer(void){
    TagList->Clear();
    TLabelInitStructure LabelInit;
    LabelInit.style = LabelsStyle::WIDTH_FIXED;
    LabelInit.Rect = {10, 10, 10, 70};
    LabelInit.focused = false;

    TagList->AddList({
        new TTagLineScrollCaptionComment("U1/RAM/Test/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/IExcTst/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/TestTime/", LabelInit),
        new TTagLineScrollCaptionComment("U1/RAM/FS+/", LabelInit),
        new TTagLineScrollCaptionComment("U1/RAM/FS-/", LabelInit),
        });
}
