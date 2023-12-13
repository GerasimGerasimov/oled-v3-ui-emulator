#include "PageReady.h"
#include "TagLine.h"
#include <FixedHeader.h>

TPageReady::TPageReady(std::string Name) : TPageSensors(Name) {
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
  LabelInit.style = LabelsStyle::WIDTH_DINAMIC;
  LabelInit.Rect = { 10, 10, 10, 10 };
  LabelInit.focused = false;
  TagList->AddList({
      new TTagLine("SyncRect", "U1/RAM/SyncRect/", LabelInit),
      new TTagLine("IexcReady", "U1/RAM/IexcReady/", LabelInit),
      new TTagLine("PWR_LNK", "U1/RAM/DExS_PWR_LNK/", LabelInit),
      new TTagLine("PWR_OK", "U1/RAM/DExS_PWR_OK/", LabelInit),
      
    });
}
