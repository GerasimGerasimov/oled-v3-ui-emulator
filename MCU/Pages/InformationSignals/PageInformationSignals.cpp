#include "PageInformationSignals.h"
#include "TagLine.h"
#include <FixedHeader.h>

TPageInformationSignals::TPageInformationSignals(std::string Name) : TPageSensors(Name) {
  TLabelInitStructure LabelInitH;
  LabelInitH.pOwner = Container;
  LabelInitH.caption = "Информационные сигналы";
  TFixedHeader* pHeader = new TFixedHeader(LabelInitH);
  delete Container->List[0];
  Container->List[0] = pHeader;

  
}

void TPageInformationSignals::fillPageContainer(void) {
  TagList->Clear();
  TLabelInitStructure LabelInit;
  LabelInit.style = LabelsStyle::WIDTH_DINAMIC;
  LabelInit.Rect = { 10, 10, 10, 10 };
  LabelInit.focused = false;
  TagList->AddList({
      new TTagLine("PWR", "U1/RAM/PWR/", LabelInit),
      new TTagLine("DIRref", "U1/RAM/DIRref/", LabelInit),
      new TTagLine("DIR", "U1/RAM/DIR/", LabelInit),
      new TTagLine("CPAUSE", "U1/RAM/CPAUSE/", LabelInit),
      new TTagLine("SRW", "U1/RAM/SRW/", LabelInit),
      new TTagLine("CLW", "U1/RAM/CLW/", LabelInit),
      new TTagLine("SpdDown", "U1/RAM/SpdDown/", LabelInit),
      new TTagLine("i2tR", "U1/RAM/i2tR/", LabelInit),

    });
}
