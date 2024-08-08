#include "PageCosSetting.h"
#include "TagLine.h"
#include "FixedHeader.h"

//cos настройка
TPageCosSetting::TPageCosSetting(std::string Name) : TPageBasicSettings(Name){
    TLabelInitStructure LabelInitH;
    LabelInitH.pOwner = Container;
    LabelInitH.caption = "cos настройка";
    TFixedHeader* pHeader = new TFixedHeader(LabelInitH);
    delete Container->List[0];
    Container->List[0] = pHeader;
}

void TPageCosSetting::fillPageContainer(void){
    TagList->Clear();
    TLabelInitStructure LabelInit;
    LabelInit.style = LabelsStyle::WIDTH_DINAMIC;
    LabelInit.Rect = {10, 10, 10, 10};
    LabelInit.focused = false;
    
    TagList->AddList({
        new TTagLine("Istat", "U1/RAM/Istat/", LabelInit),
        new TTagLine("Ir", "U1/RAM/Ir/", LabelInit),
        new TTagLine("F", "U1/RAM/F/", LabelInit),
        new TTagLine("FRef", "U1/RAM/FRef/", LabelInit),
        new TTagLine("CFI_OFFSET", "U1/CD/CFI_OFFSET/", LabelInit),
        new TTagLine("TfFi", "U1/CD/TfFi/", LabelInit),
        new TTagLine("FiRef", "U1/FLASH/FiRef/", LabelInit),
        new TTagLine("TiFi", "U1/FLASH/TiFi/", LabelInit),
        new TTagLine("IzBias", "U1/FLASH/IzBias/", LabelInit),
        new TTagLine("FLmax", "U1/FLASH/FLmax/", LabelInit),
        new TTagLine("FLmin", "U1/FLASH/FLmin/", LabelInit),
        new TTagLine("Pnom", "U1/FLASH/Pnom/", LabelInit),
        new TTagLine("QminP0", "U1/FLASH/QminP0/", LabelInit),
        new TTagLine("QminP1", "U1/FLASH/QminP1/", LabelInit),
        new TTagLine("dQmin", "U1/FLASH/dQmin/", LabelInit),
        new TTagLine("QmaxP0", "U1/FLASH/QmaxP0/", LabelInit),
        new TTagLine("QmaxP1", "U1/FLASH/QmaxP1/", LabelInit),
        });
}
