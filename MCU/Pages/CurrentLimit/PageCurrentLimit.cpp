#include "PageCurrentLimit.h"
#include "TagLine.h"
#include "FixedHeader.h"

//Ограничение тока
TPageCurrentLimit::TPageCurrentLimit(std::string Name) : TPageSensors(Name){
    TLabelInitStructure LabelInitH;
    LabelInitH.pOwner = Container;
    LabelInitH.caption = "Ограничение тока";
    TFixedHeader* pHeader = new TFixedHeader(LabelInitH);
    delete Container->List[0];
    Container->List[0] = pHeader;
}

void TPageCurrentLimit::fillPageContainer(void){
    TagList->Clear();
    TLabelInitStructure LabelInit;
    LabelInit.style = LabelsStyle::WIDTH_DINAMIC;
    LabelInit.Rect = {10, 10, 10, 10};
    LabelInit.focused = false;

    TagList->AddList({
        new TTagLine("IExcRef_min", "U1/RAM/IExcRef_min/", LabelInit),
        new TTagLine("IExcRef_max", "U1/RAM/IExcRef_max/", LabelInit),
        new TTagLine("imp_block", "U1/RAM/imp_block/", LabelInit),
        new TTagLine("i2tR", "U1/RAM/i2tR/", LabelInit),
        new TTagLine("EExcReg", "U1/RAM/EExcReg/", LabelInit),
        new TTagLine("IExcRef", "U1/RAM/IExcRef/", LabelInit),
        new TTagLine("IExcRefAuto", "U1/RAM/IExcRefAuto/", LabelInit),
        new TTagLine("IExcRefReg", "U1/RAM/IExcRefReg/", LabelInit),
        new TTagLine("IExcMin", "U1/FLASH/IExcMin/", LabelInit),
        new TTagLine("IExcMax", "U1/FLASH/IExcMax/", LabelInit),
        new TTagLine("IExcManuMax", "U1/FLASH/IExcManuMax/", LabelInit),
        new TTagLine("iIExci2tOvOnR", "U1/FLASH/iIExci2tOvOnR/", LabelInit),
        new TTagLine("iIExci2tOvOffR", "U1/FLASH/iIExci2tOvOffR/", LabelInit),
        new TTagLine("IExcI2tRef", "U1/FLASH/IExcI2tRef/", LabelInit),
        new TTagLine("IExcWinDry", "U1/FLASH/IExcWinDry/", LabelInit),
        });
}
