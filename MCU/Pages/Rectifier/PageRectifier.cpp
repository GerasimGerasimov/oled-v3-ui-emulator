#include "PageRectifier.h"
#include "TagLineVarSize.h"
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
      new TTagLine("PWR_OK", "U1/RAM/DExS_PWR_OK/", LabelInit),
      new TTagLine("PWR_LNK", "U1/RAM/DExS_PWR_LNK/", LabelInit),
      new TTagLine("SyncRect", "U1/RAM/SyncRect/", LabelInit),
      new TTagLine("stPWRFltEn", "U1/FLASH/stPWRFltEnable/", LabelInit),
      new TTagLine("FreqRect", "U1/RAM/FreqRect/", LabelInit),
      new TTagLine("Vab", "U1/RAM/Vab/", LabelInit),
      new TTagLine("Vbc", "U1/RAM/Vbc/", LabelInit),
      new TTagLine("Vca", "U1/RAM/Vca/", LabelInit),
      new TTagLine("Amax", "U1/FLASH/Amax/", LabelInit),
      new TTagLine("Amin", "U1/FLASH/Amin/", LabelInit),
      new TTagLine("Ablank", "U1/FLASH/Ablank/", LabelInit),
      new TTagLine("FieldBlankT", "U1/FLASH/FieldBlankTime/", LabelInit),
      new TTagLineVarSize("UmaxSpRect", "U1/FLASH/UmaxSpRect/", LabelInit, 0),
      new TTagLineVarSize("UminSpRect", "U1/FLASH/UminSpRect/", LabelInit, 0),
      new TTagLineVarSize("FmaxSpRect", "U1/FLASH/FmaxSpRect/", LabelInit, 0),
      new TTagLineVarSize("FminSpRect", "U1/FLASH/FminSpRect/", LabelInit, 0),
      new TTagLine("SUPPLFltT", "U1/FLASH/SUPPLFltTime/", LabelInit),
    });
  dynamic_cast<TTagLineVarSize*>(TagList->List[12])->setGap(3);//UmaxSpRect
  dynamic_cast<TTagLineVarSize*>(TagList->List[13])->setGap(4);//UminSpRect
  dynamic_cast<TTagLineVarSize*>(TagList->List[14])->setGap(2);//FmaxSpRect
  dynamic_cast<TTagLineVarSize*>(TagList->List[15])->setGap(3);//FminSpRect
}
