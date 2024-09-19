#include "PageControlParameters.h"
#include "TagLine.h"
#include <FixedHeader.h>

TPageControlParameters::TPageControlParameters(std::string Name) : TPageSensors(Name) {
  TLabelInitStructure LabelInitH;
  LabelInitH.pOwner = Container;
  LabelInitH.caption = "�����. ���������";
  TFixedHeader* pHeader = new TFixedHeader(LabelInitH);
  delete Container->List[0];
  Container->List[0] = pHeader;
}

void TPageControlParameters::fillPageContainer(void) {
  TagList->Clear();
  TLabelInitStructure LabelInit;
  LabelInit.style = LabelsStyle::WIDTH_DINAMIC;
  LabelInit.Rect = { 10, 10, 10, 10 };
  LabelInit.focused = false;
  TagList->AddList({
      new TTagLine("�����.����", "U1/RAM/SpdRef/", LabelInit),
      new TTagLine("U.���.���.", "U1/RAM/Utg/", LabelInit),
      new TTagLine("U.�����", "U1/RAM/Uref/", LabelInit),
      new TTagLine("���� ���", "U1/RAM/A/", LabelInit),
      new TTagLine("EngTmp", "U1/RAM/EngTmp/", LabelInit),
      new TTagLine("TCC", "U1/RAM/TCC/", LabelInit),
      new TTagLine("SpdRefK", "U1/RAM/SpdRefK/", LabelInit),
      
    });
}
