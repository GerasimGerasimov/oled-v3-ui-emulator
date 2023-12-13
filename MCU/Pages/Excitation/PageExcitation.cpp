#include "PageExcitation.h"
#include "TagLine.h"
#include <FixedHeader.h>

TPageExcitation::TPageExcitation(std::string Name) : TPageSensors(Name) {
  TLabelInitStructure LabelInitH;
  LabelInitH.pOwner = Container;
  LabelInitH.caption = "Возбуждение";
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
      new TTagLine("Ток возб", "U1/RAM/Iexc/", LabelInit),
      new TTagLine("Напр возб", "U1/RAM/Uexc/", LabelInit),
      new TTagLine("IexcReady", "U1/RAM/IexcReady/", LabelInit),
      new TTagLine("Мин.ток воз-я", "U1/FLASH/fIexcMin/", LabelInit),
    });
}
