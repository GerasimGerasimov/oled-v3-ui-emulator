#include "TpageGeneratorProtection.h"
#include "TagLineScrollCaptionComment.h"
#include <FixedHeader.h>


TpageGeneratorProtection::TpageGeneratorProtection(std::string Name) : TPageControlSettings(Name) {
    TLabelInitStructure LabelInitH;
    LabelInitH.pOwner = Container;
    LabelInitH.caption = "Защиты от ген. режим";
    TFixedHeader* pHeader = new TFixedHeader(LabelInitH);
    delete Container->List[0];
    Container->List[0] = pHeader;
}

void TpageGeneratorProtection::fillPageContainer(void) {
    TagList->Clear();
    TLabelInitStructure LabelInit;
    LabelInit.style = LabelsStyle::WIDTH_FIXED;
    LabelInit.Rect = { 10, 10, 10, 90 };
    LabelInit.focused = false;
    TagList->AddList({
        new TTagLineScrollCaptionComment("U1/RAM/GMP/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/stGenMdFltEnable/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/stGenModeSelect/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/GMPU/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/GMPUFltTime/", LabelInit),

        });
    dynamic_cast<TTagLine*>(TagList->List[0])->setValueLeft(90);
    dynamic_cast<TTagLine*>(TagList->List[1])->setValueLeft(90);
    dynamic_cast<TTagLine*>(TagList->List[2])->setValueLeft(90);

}
