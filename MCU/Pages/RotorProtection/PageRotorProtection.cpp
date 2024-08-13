#include "PageRotorProtection.h"
#include "TagLineScrollCaption.h"
#include <FixedHeader.h>

TPageRotorProtection::TPageRotorProtection(std::string Name) : TPageBasicSettings(Name){
    TLabelInitStructure LabelInitH;
    LabelInitH.pOwner = Container;
    LabelInitH.caption = "Защиты ротора";
    TFixedHeader* pHeader = new TFixedHeader(LabelInitH);
    delete Container->List[0];
    Container->List[0] = pHeader;
}

void TPageRotorProtection::fillPageContainer(void){
    TagList->Clear();
    TLabelInitStructure LabelInit;
    LabelInit.style = LabelsStyle::WIDTH_DINAMIC;
    LabelInit.Rect = {10, 10, 10, 10};
    LabelInit.focused = false;
    TagList->AddList({
        new TTagLine("IrMaxFlt", "U1/FLASH/IrMaxFlt/", LabelInit),
        new TTagLine("stFieldFltEn", "U1/FLASH/stFieldFltEnable/", LabelInit),
        new TTagLine("FieldFailT", "U1/FLASH/FieldFailTime/", LabelInit),
        new TTagLine("fIrFieldFail", "U1/FLASH/fIrFieldFail/", LabelInit),
        new TTagLine("Ti2tR", "U1/FLASH/Ti2tR/", LabelInit),
        new TTagLineScrollCaption("iIExci2tOvOnR", "U1/FLASH/iIExci2tOvOnR/", LabelInit),
        new TTagLineScrollCaption("iIExci2tOvOffR", "U1/FLASH/iIExci2tOvOffR/", LabelInit),
        new TTagLine("IExcI2tRef", "U1/FLASH/IExcI2tRef/", LabelInit),
        });
}
