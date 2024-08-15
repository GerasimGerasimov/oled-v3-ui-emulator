#include "PageRectifier.h"
#include "TagLineScrollCaptionComment.h"
#include <FixedHeader.h>

TPageRectifier::TPageRectifier(std::string Name) : TPageControlSettings(Name){
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
  LabelInit.style = LabelsStyle::WIDTH_FIXED;
  LabelInit.Rect = { 10, 10, 10, 70 };
  LabelInit.focused = false;
  TagList->AddList({
      new TTagLineScrollCaptionComment("U1/RAM/DExS_PWR_OK/", LabelInit),
      new TTagLineScrollCaptionComment("U1/RAM/DExS_PWR_LNK/", LabelInit),
      new TTagLineScrollCaptionComment("U1/RAM/SyncRect/", LabelInit),
      new TTagLineScrollCaptionComment("U1/FLASH/stPWRFltEnable/", LabelInit),
      new TTagLineScrollCaptionComment("U1/RAM/FreqRect/", LabelInit),
      new TTagLineScrollCaptionComment("U1/RAM/Vab/", LabelInit),
      new TTagLineScrollCaptionComment("U1/RAM/Vbc/", LabelInit),
      new TTagLineScrollCaptionComment("U1/RAM/Vca/", LabelInit),
      new TTagLineScrollCaptionComment("U1/FLASH/Amax/", LabelInit),
      new TTagLineScrollCaptionComment("U1/FLASH/Amin/", LabelInit),
      new TTagLineScrollCaptionComment("U1/FLASH/Ablank/", LabelInit),
      new TTagLineScrollCaptionComment("U1/FLASH/FieldBlankTime/", LabelInit),
      new TTagLineScrollCaptionComment("U1/FLASH/UmaxSpRect/", LabelInit),
      new TTagLineScrollCaptionComment("U1/FLASH/UminSpRect/", LabelInit),
      new TTagLineScrollCaptionComment("U1/FLASH/FmaxSpRect/", LabelInit),
      new TTagLineScrollCaptionComment("U1/FLASH/FminSpRect/", LabelInit),
      new TTagLineScrollCaptionComment("U1/FLASH/SUPPLFltTime/", LabelInit),
    });
}
