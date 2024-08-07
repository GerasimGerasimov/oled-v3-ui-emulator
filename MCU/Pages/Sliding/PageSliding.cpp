#include "PageSliding.h"
#include "TagLine.h"
#include "FixedHeader.h"

//Скольжение
TPageSliding::TPageSliding(std::string Name) : TPageSensors(Name){
    TLabelInitStructure LabelInitH;
    LabelInitH.pOwner = Container;
    LabelInitH.caption = "Скольжение";
    TFixedHeader* pHeader = new TFixedHeader(LabelInitH);
    delete Container->List[0];
    Container->List[0] = pHeader;
}

void TPageSliding::fillPageContainer(void){
    TagList->Clear();
    TLabelInitStructure LabelInit;
    LabelInit.style = LabelsStyle::WIDTH_DINAMIC;
    LabelInit.Rect = {10, 10, 10, 10};
    LabelInit.focused = false;

    TagList->AddList({
        new TTagLine("Чтото", "U1/RAM/None/", LabelInit),

        });
}