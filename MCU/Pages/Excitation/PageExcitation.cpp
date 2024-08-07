#include "PageExcitation.h"
#include "TagLine.h"
#include <FixedHeader.h>

TPageExcitation::TPageExcitation(std::string Name) : TPageBasicSettings(Name){
  TLabelInitStructure LabelInitH;
  LabelInitH.pOwner = Container;
  LabelInitH.caption = "Подача возбуждения";
  TFixedHeader* pHeader = new TFixedHeader(LabelInitH);
  delete Container->List[0];
  Container->List[0] = pHeader;
}

void TPageExcitation::fillPageContainer(void) {
  TagList->Clear();
  TLabelInitStructure LabelInit;
  LabelInit.style = LabelsStyle::WIDTH_DINAMIC;
  LabelInit.Rect = { 10, 10, 10, 10 };
  LabelInit.focused = false;
  TagList->AddList({
      new TTagLine("IstStart", "U1/FLASH/IstStart/", LabelInit),
      new TTagLine("IstStop", "U1/FLASH/IstStop/", LabelInit),
      new TTagLine("IstExcEnable", "U1/FLASH/IstExcEnable/", LabelInit),
      new TTagLine("ExcEnableFreq", "U1/FLASH/ExcEnableFreq/", LabelInit),
      new TTagLine("HsFreq", "U1/FLASH/HsFreq/", LabelInit),
      new TTagLine("HsTime", "U1/FLASH/HsTime/", LabelInit),
      new TTagLine("IExcRef", "U1/FLASH/IExcRef/", LabelInit),
      new TTagLine("IExcForce", "U1/FLASH/IExcForce/", LabelInit),
      new TTagLine("StartForceTime", "U1/FLASH/StartForceTime/", LabelInit),
      new TTagLine("IstOffTime", "U1/FLASH/IstOffTime/", LabelInit),
      new TTagLine("FieldBlankTime", "U1/FLASH/FieldBlankTime/", LabelInit),
      new TTagLine("NextStartTime", "U1/FLASH/NextStartTime/", LabelInit),
      new TTagLine("FSAsyncTime", "U1/FLASH/FSAsyncTime/", LabelInit),
      new TTagLine("QminAsyncTime", "U1/FLASH/QminAsyncTime/", LabelInit),
      new TTagLine("WaitStable", "U1/FLASH/WaitStable/", LabelInit),
      new TTagLine("TIexcRefChangeTime", "U1/FLASH/TIexcRefChangeTime/", LabelInit),
      new TTagLine("TIexcForceDwnTime", "U1/FLASH/TIexcForceDwnTime/", LabelInit),
      new TTagLine("TIexcForceUpTime", "U1/FLASH/TIexcForceUpTime/", LabelInit),
      new TTagLine("IExcMin", "U1/FLASH/IExcMin/", LabelInit),
      new TTagLine("IExcMax", "U1/FLASH/IExcMax/", LabelInit),
      new TTagLine("IExcManuMax", "U1/FLASH/IExcManuMax/", LabelInit),
    });
}
