#include "PageRegulatorSettings.h"
#include "TagLine.h"
#include <FixedHeader.h>

TPageRegulatorSettings::TPageRegulatorSettings(std::string Name) : TPageBasicSettings(Name) {
  TLabelInitStructure LabelInitH;
  LabelInitH.pOwner = Container;
  LabelInitH.caption = "������� ����������";
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
      new TTagLine("Remote", "U1/FLASH/Remote/", LabelInit),
      new TTagLine("�.���� ����", "U1/FLASH/SKp/", LabelInit),
      new TTagLine("�.���� ����", "U1/FLASH/CKp/", LabelInit),
      new TTagLine("���.� �����", "U1/FLASH/STi/", LabelInit),
      new TTagLine("����.� ��", "U1/FLASH/Tro/", LabelInit),
      new TTagLine("���.� �����", "U1/FLASH/STd/", LabelInit),
      new TTagLine("FbType", "U1/FLASH/FbType/", LabelInit),
    });
}
