#include "PageThermalProtection.h"
#include "TagLine.h"
#include <FixedHeader.h>

TPageThermalProtection::TPageThermalProtection(std::string Name) : TPageBasicSettings(Name) {
  TLabelInitStructure LabelInitH;
  LabelInitH.pOwner = Container;
  LabelInitH.caption = "Тепловая защита";
  TFixedHeader* pHeader = new TFixedHeader(LabelInitH);
  delete Container->List[0];
  Container->List[0] = pHeader;
}

void TPageThermalProtection::fillPageContainer(void) {
  TagList->Clear();
  TLabelInitStructure LabelInit;
  LabelInit.style = LabelsStyle::WIDTH_DINAMIC;
  LabelInit.Rect = { 10, 10, 10, 10 };
  LabelInit.focused = false;

  TagList->AddList({
      new TTagLine("Тпост нагр охл", "U1/FLASH/Ti2tR/", LabelInit),
      new TTagLine("Нагрев", "U1/FLASH/i2tOV_ON/", LabelInit),
      new TTagLine("Восстан", "U1/FLASH/i2tOV_OFF/", LabelInit),
      new TTagLine("TEngOVH", "U1/FLASH/TEngOVH/", LabelInit),
    });
}
