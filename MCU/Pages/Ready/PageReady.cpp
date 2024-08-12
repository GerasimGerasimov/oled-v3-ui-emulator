#include "PageReady.h"
#include "TagLine.h"
#include "TagLineVarSize.h"
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
      new TTagLine("iReady", "U1/RAM/iReady/", LabelInit),
      new TTagLine("iMPSState", "U1/RAM/iMPSState/", LabelInit),
      new TTagLineVarSize("DExS_PWR_OK", "U1/RAM/DExS_PWR_OK/", LabelInit, 0),
      new TTagLine("FAULT", "U1/RAM/FAULT/", LabelInit),
      new TTagLine("SlideCirctErr", "U1/RAM/SlideCirctErr/", LabelInit),
      new TTagLine("Test", "U1/RAM/Test/", LabelInit),
      new TTagLineVarSize("NxtStrtDisable", "U1/RAM/NxtStrtDisable/", LabelInit, 0),
      new TTagLine("i2tR", "U1/RAM/i2tR/", LabelInit),
      new TTagLine("UstFail", "U1/RAM/UstFail/", LabelInit),
      new TTagLine("iMMSState", "U1/RAM/iMMSState/", LabelInit),
      new TTagLine("IstStartTrig", "U1/RAM/IstStartTrig/", LabelInit),
      new TTagLine("PWR", "U1/RAM/PWR/", LabelInit),
    });
}
