#include "PageReady.h"
#include "TagLineScrollCaptionComment.h"
#include <FixedHeader.h>

TPageReady::TPageReady(std::string Name) : TPageControlSettings(Name) {
  TLabelInitStructure LabelInitH;
  LabelInitH.pOwner = Container;
  LabelInitH.caption = "Готовность";
  TFixedHeader* pHeader = new TFixedHeader(LabelInitH);
  delete Container->List[0];
  Container->List[0] = pHeader;
}

void TPageReady::fillPageContainer(void) {
  TagList->Clear();
  TLabelInitStructure LabelInit;
  LabelInit.style = LabelsStyle::WIDTH_FIXED;
  LabelInit.Rect = { 10, 10, 10, 105 };
  LabelInit.focused = false;
  TagList->AddList({
      new TTagLineScrollCaptionComment("U1/RAM/iReady/", LabelInit),
      new TTagLineScrollCaptionComment("U1/FLASH/stReadyOnInRun/", LabelInit),
      new TTagLineScrollCaptionComment("U1/RAM/iMPSState/", LabelInit),
      new TTagLineScrollCaptionComment("U1/RAM/FAULT/", LabelInit),
      new TTagLineScrollCaptionComment("U1/RAM/DExS_PWR_OK/", LabelInit),
      new TTagLineScrollCaptionComment("U1/RAM/Test/", LabelInit),
      new TTagLineScrollCaptionComment("U1/RAM/NxtStrtDisable/", LabelInit),
      new TTagLineScrollCaptionComment("U1/RAM/i2tR/", LabelInit),
      new TTagLineScrollCaptionComment("U1/RAM/UstFail/", LabelInit),
      new TTagLineScrollCaptionComment("U1/FLASH/stUstFltReadyEnable/", LabelInit),
      new TTagLineScrollCaptionComment("U1/RAM/iMMSState/", LabelInit),
      new TTagLineScrollCaptionComment("U1/RAM/IstStartTrig/", LabelInit),
      new TTagLineScrollCaptionComment("U1/RAM/PWR/", LabelInit),
      new TTagLineScrollCaptionComment("U1/RAM/SspRefLost/", LabelInit),
    });

  int const totalTags = 14;

  for (int i = 0; i < totalTags; i++) {
      if (TTagLine* tagLine = dynamic_cast<TTagLine*>(TagList->List[i])) {
          tagLine->setValueLeft(105);
      }
  }
  for (int i = 0; i < totalTags; i++) {
      if (TTagLine* tagLine = dynamic_cast<TTagLine*>(TagList->List[i])) {
          tagLine->setMsuLeft(115);
      }
  }

}
