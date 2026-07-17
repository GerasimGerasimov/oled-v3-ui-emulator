#include "PageTaskLimit.h"
#include "TagLineScrollCaptionComment.h"
#include <FixedHeader.h>

TPageTaskLimit::TPageTaskLimit(std::string Name) : TPageBasicSettings(Name){
    TLabelInitStructure LabelInitH;
    LabelInitH.pOwner = Container;
    LabelInitH.caption = "Огран. задания";
    TFixedHeader* pHeader = new TFixedHeader(LabelInitH);
    delete Container->List[0];
    Container->List[0] = pHeader;
}

void TPageTaskLimit::fillPageContainer(void){
    TagList->Clear();
    TLabelInitStructure LabelInit;
    LabelInit.style = LabelsStyle::WIDTH_FIXED;
    LabelInit.Rect = {10, 10, 10, 80};
    LabelInit.focused = false;
    TagList->AddList({
        new TTagLineScrollCaption("Min ток возбуждения", "U1/FLASH/IExcMin/", LabelInit),
        new TTagLineScrollCaption("Max ток возбуждения", "U1/FLASH/IExcMax/", LabelInit),
        new TTagLineScrollCaption("Max ток возб. в ручном режиме", "U1/FLASH/IExcManuMax/", LabelInit),
        new TTagLineScrollCaption("Max заданный угол Фи", "U1/FLASH/FLmax/", LabelInit),
        new TTagLineScrollCaption("Min заданный угол Фи", "U1/FLASH/FLmin/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/dIExcRef/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/dFiRef/", LabelInit)
        });
}
