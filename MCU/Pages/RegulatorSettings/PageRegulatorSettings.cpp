#include "PageRegulatorSettings.h"
#include "TagLineScrollCaptionComment.h"
#include <FixedHeader.h>

TPageRegulatorSettings::TPageRegulatorSettings(std::string Name) : TPageBasicSettings(Name) {
  TLabelInitStructure LabelInitH;
  LabelInitH.pOwner = Container;
  LabelInitH.caption = "Настройки ПИД рег.";
  TFixedHeader* pHeader = new TFixedHeader(LabelInitH);
  delete Container->List[0];
  Container->List[0] = pHeader;
}

void TPageRegulatorSettings::fillPageContainer(void) {
  TagList->Clear();
  TLabelInitStructure LabelInit;
  LabelInit.style = LabelsStyle::WIDTH_DINAMIC;
  LabelInit.Rect = { 10, 10, 10, 10 };
  LabelInit.focused = false;

  TagList->AddList({
      new TTagLineScrollCaptionComment("U1/FLASH/Ti/", LabelInit),
      new TTagLineScrollCaptionComment("U1/FLASH/Ku/", LabelInit),
      new TTagLineScrollCaptionComment("U1/FLASH/Td/", LabelInit),
    });
}
