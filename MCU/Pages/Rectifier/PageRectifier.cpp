#include "PageRectifier.h"
#include "TagLine.h"
#include <FixedHeader.h>

TPageRectifier::TPageRectifier(std::string Name) : TPageBasicSettings(Name){
  TLabelInitStructure LabelInitH;
  LabelInitH.pOwner = Container;
  LabelInitH.caption = "Выпрямитель";
  TFixedHeader* pHeader = new TFixedHeader(LabelInitH);
  delete Container->List[0];
  Container->List[0] = pHeader;
}

void TPageRectifier::fillPageContainer(void) {
  TagList->Clear();
  TLabelInitStructure LabelInit;
  LabelInit.style = LabelsStyle::WIDTH_DINAMIC;
  LabelInit.Rect = { 10, 10, 10, 10 };
  LabelInit.focused = false;
  TagList->AddList({
      new TTagLine("DExS_PWR_OK", "U1/RAM/DExS_PWR_OK/", LabelInit),
      new TTagLine("DExS_PWR_LNK", "U1/RAM/DExS_PWR_LNK/", LabelInit),
      new TTagLine("SyncRect", "U1/RAM/SyncRect/", LabelInit),
      new TTagLine("stPWRFltEnable", "U1/FLASH/stPWRFltEnable/", LabelInit),
      new TTagLine("FreqRect", "U1/RAM/FreqRect/", LabelInit),
      new TTagLine("Vab", "U1/RAM/Vab/", LabelInit),
      new TTagLine("Vbc", "U1/RAM/Vbc/", LabelInit),
      new TTagLine("Vca", "U1/RAM/Vca/", LabelInit),
      new TTagLine("Amax", "U1/FLASH/Amax/", LabelInit),
      new TTagLine("Amin", "U1/FLASH/Amin/", LabelInit),
      new TTagLine("Ablank", "U1/FLASH/Ablank/", LabelInit),
      new TTagLine("FieldBlankTime", "U1/FLASH/FieldBlankTime/", LabelInit),
      new TTagLine("UmaxSpRect", "U1/FLASH/UmaxSpRect/", LabelInit),
      new TTagLine("UminSpRect", "U1/FLASH/UminSpRect/", LabelInit),
      new TTagLine("FmaxSpRect", "U1/FLASH/FmaxSpRect/", LabelInit),
      new TTagLine("FminSpRect", "U1/FLASH/FminSpRect/", LabelInit),
      new TTagLine("SUPPLFltTime", "U1/FLASH/SUPPLFltTime/", LabelInit),
    });
}
