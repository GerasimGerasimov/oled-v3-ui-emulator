#include "PageTesting.h"
#include "TagLine.h"
#include "FixedHeader.h"

//Опробование
TPageTesting::TPageTesting(std::string Name) : TPageSensors(Name){
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
    LabelInit.style = LabelsStyle::WIDTH_DINAMIC;
    LabelInit.Rect = {10, 10, 10, 10};
    LabelInit.focused = false;

    TagList->AddList({
        new TTagLine("Test", "U1/RAM/Test/", LabelInit),
        new TTagLine("IExcTst", "U1/FLASH/IExcTst/", LabelInit),
        new TTagLine("TestTime", "U1/FLASH/TestTime/", LabelInit),
        new TTagLine("FS+", "U1/RAM/FS+/", LabelInit),
        new TTagLine("FS-", "U1/RAM/FS-/", LabelInit),
        });
}
