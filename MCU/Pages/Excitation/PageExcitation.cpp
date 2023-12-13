#include "PageExcitation.h"
#include "TagLine.h"
#include <FixedHeader.h>

TPageExcitation::TPageExcitation(std::string Name) : TPageSensors(Name) {
  TLabelInitStructure LabelInitH;
  LabelInitH.pOwner = Container;
  LabelInitH.caption = "�����������";
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
      new TTagLine("��� ����", "U1/RAM/Iexc/", LabelInit),
      new TTagLine("���� ����", "U1/RAM/Uexc/", LabelInit),
      new TTagLine("IexcReady", "U1/RAM/IexcReady/", LabelInit),
      new TTagLine("���.��� ���-�", "U1/FLASH/fIexcMin/", LabelInit),
    });
}
