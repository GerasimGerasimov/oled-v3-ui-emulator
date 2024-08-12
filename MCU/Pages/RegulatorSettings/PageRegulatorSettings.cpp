#include "PageRegulatorSettings.h"
#include "TagLine.h"
#include <FixedHeader.h>

TPageRegulatorSettings::TPageRegulatorSettings(std::string Name) : TPageBasicSettings(Name) {
  TLabelInitStructure LabelInitH;
  LabelInitH.pOwner = Container;
  LabelInitH.caption = "Настройки ПИД регулятора";
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
      new TTagLine("Ti", "U1/FLASH/Ti/", LabelInit),
      new TTagLine("Ku", "U1/FLASH/Ku/", LabelInit),
      new TTagLine("Td", "U1/FLASH/Td/", LabelInit),
    });
}
