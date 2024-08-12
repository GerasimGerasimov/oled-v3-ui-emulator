#include "PagePower.h"
#include "TagLine.h"
#include "FixedHeader.h"

TPagePower::TPagePower(std::string Name) : TPageSensors(Name){
    TLabelInitStructure LabelInitH;
    LabelInitH.pOwner = Container;
    LabelInitH.caption = "Мощность";
    TFixedHeader* pHeader = new TFixedHeader(LabelInitH);
    delete Container->List[0];
    Container->List[0] = pHeader;
}

void TPagePower::fillPageContainer(void){
    TagList->Clear();
    TLabelInitStructure LabelInit;
    LabelInit.style = LabelsStyle::WIDTH_DINAMIC;
    LabelInit.Rect = {10, 10, 10, 10};
    LabelInit.focused = false;

    TagList->AddList({
        new TTagLine("Ssg", "U1/RAM/Ssg/", LabelInit),
        new TTagLine("Psg", "U1/RAM/Psg/", LabelInit),
        new TTagLine("Qsg", "U1/RAM/Qsg/", LabelInit),
        new TTagLine("Qoe", "U1/RAM/Qoe/", LabelInit),
        new TTagLine("QLimMin", "U1/RAM/QLimMin/", LabelInit),
        new TTagLine("QLimMax", "U1/RAM/QLimMax/", LabelInit),

        });
}
