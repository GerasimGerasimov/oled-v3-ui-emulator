#include "PageFieldBreak.h"
#include "TagLine.h"
#include "FixedHeader.h"

//Обрыв поля
TPageFieldBreak::TPageFieldBreak(std::string Name) : TPageBasicSettings(Name){
    TLabelInitStructure LabelInitH;
    LabelInitH.pOwner = Container;
    LabelInitH.caption = "Обрыв поля";
    TFixedHeader* pHeader = new TFixedHeader(LabelInitH);
    delete Container->List[0];
    Container->List[0] = pHeader;
}

void TPageFieldBreak::fillPageContainer(void){
    TagList->Clear();
    TLabelInitStructure LabelInit;
    LabelInit.style = LabelsStyle::WIDTH_DINAMIC;
    LabelInit.Rect = {10, 10, 10, 10};
    LabelInit.focused = false;

    TagList->AddList({
        new TTagLine("FieldFail", "U1/RAM/FieldFail/", LabelInit),
        new TTagLine("FieldFailTime", "U1/FLASH/FieldFailTime/", LabelInit),
        new TTagLine("fIrFieldFail", "U1/FLASH/fIrFieldFail/", LabelInit),
        new TTagLine("stFieldFltEnable", "U1/FLASH/stFieldFltEnable/", LabelInit),
        });
}
