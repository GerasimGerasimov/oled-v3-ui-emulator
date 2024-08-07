#include "PageAutoMode.h"
#include "TagLine.h"
#include "FixedHeader.h"

//Автоматический режим
TPageAutoMode::TPageAutoMode(std::string Name) : TPageBasicSettings(Name){
    TLabelInitStructure LabelInitH;
    LabelInitH.pOwner = Container;
    LabelInitH.caption = "Автомат. режим";
    TFixedHeader* pHeader = new TFixedHeader(LabelInitH);
    delete Container->List[0];
    Container->List[0] = pHeader;
}

void TPageAutoMode::fillPageContainer(void){
    TagList->Clear();
    TLabelInitStructure LabelInit;
    LabelInit.style = LabelsStyle::WIDTH_DINAMIC;
    LabelInit.Rect = {10, 10, 10, 10};
    LabelInit.focused = false;

    TagList->AddList({
        new TTagLine("QminLimIrUp", "U1/RAM/QminLimIrUp/", LabelInit),
        new TTagLine("QmaxLimIrDn", "U1/RAM/QmaxLimIrDn/", LabelInit),
        new TTagLine("F", "U1/RAM/F/", LabelInit),
        new TTagLine("Freq", "U1/RAM/Freq/", LabelInit),
        new TTagLine("Ssg", "U1/RAM/Ssg/", LabelInit),
        new TTagLine("Psg", "U1/RAM/Psg/", LabelInit),
        new TTagLine("Qsg", "U1/RAM/Qsg/", LabelInit),
        new TTagLine("Qoe", "U1/RAM/Qoe/", LabelInit),
        new TTagLine("QLimMin", "U1/RAM/QLimMin/", LabelInit),
        new TTagLine("QLimMax", "U1/RAM/QLimMax/", LabelInit),
        new TTagLine("FRef", "U1/RAM/FRef/", LabelInit),
        new TTagLine("AutoMode", "U1/FLASH/AutoMode/", LabelInit),
        new TTagLine("FiRef", "U1/FLASH/FiRef/", LabelInit),
        new TTagLine("TiFi", "U1/FLASH/TiFi/", LabelInit),
        new TTagLine("IzBias", "U1/FLASH/IzBias/", LabelInit),
        new TTagLine("FLmax", "U1/FLASH/FLmax/", LabelInit),
        new TTagLine("FLmin", "U1/FLASH/FLmin/", LabelInit),
        new TTagLine("QminP0", "U1/FLASH/QminP0/", LabelInit),
        new TTagLine("QminP1", "U1/FLASH/QminP1/", LabelInit),
        new TTagLine("dQmin", "U1/FLASH/dQmin/", LabelInit),
        new TTagLine("QmaxP0", "U1/FLASH/QmaxP0/", LabelInit),
        new TTagLine("QmaxP1", "U1/FLASH/QmaxP1/", LabelInit),
        new TTagLine("dIExcRef", "U1/FLASH/dIExcRef/", LabelInit),
        new TTagLine("dFiRef", "U1/FLASH/dFiRef/", LabelInit),
        new TTagLine("IsARV4", "U1/FLASH/IsARV4/", LabelInit),
        new TTagLine("KIsARV4", "U1/FLASH/KIsARV4/", LabelInit),
        });
}
