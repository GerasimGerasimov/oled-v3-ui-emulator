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
  LabelInit.Rect = { 10, 10, 10, 80 };
  LabelInit.focused = false;
  TagList->AddList({
      new TTagLineScrollCaptionComment("U1/RAM/DExS_PWR_LNK/", LabelInit),
      new TTagLineScrollCaptionComment("U1/RAM/SyncRect/", LabelInit),
      new TTagLineScrollCaptionComment("U1/FLASH/stPWRFltEnable/", LabelInit),
      new TTagLineScrollCaptionComment("U1/RAM/FreqRect/", LabelInit),
      new TTagLineScrollCaptionComment("U1/RAM/Vab/", LabelInit),
      new TTagLineScrollCaptionComment("U1/RAM/Vbc/", LabelInit),
      new TTagLineScrollCaptionComment("U1/RAM/Vca/", LabelInit),
      new TTagLineScrollCaption("Max угол управления", "U1/FLASH/Amax/", LabelInit),
      new TTagLineScrollCaption("Min угол управления", "U1/FLASH/Amin/", LabelInit),
      new TTagLineScrollCaption("Max угол при гашении поля", "U1/FLASH/Ablank/", LabelInit),
      new TTagLineScrollCaptionComment("U1/FLASH/FieldBlankTime/", LabelInit),
      new TTagLineScrollCaption("Max напряжение питания выпрямителя", "U1/FLASH/UmaxSpRect/", LabelInit),
      new TTagLineScrollCaption("Min напряжение питания выпрямителя", "U1/FLASH/UminSpRect/", LabelInit),
      new TTagLineScrollCaption("Max частота питания выпрямителя", "U1/FLASH/FmaxSpRect/", LabelInit),
      new TTagLineScrollCaption("Min частота питания выпрямителя", "U1/FLASH/FminSpRect/", LabelInit),
      new TTagLineScrollCaptionComment("U1/FLASH/SUPPLFltTime/", LabelInit),
    });

}
