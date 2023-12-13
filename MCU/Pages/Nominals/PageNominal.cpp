#include "PageNominal.h"
#include "TagLine.h"
#include <FixedHeader.h>




TPageNominal::TPageNominal(std::string Name) : TPageBasicSettings(Name) {
  TLabelInitStructure LabelInitH;
  LabelInitH.pOwner = Container;
  LabelInitH.caption = "��������";
  TFixedHeader* pHeader = new TFixedHeader(LabelInitH);
  delete Container->List[0];
  Container->List[0] = pHeader;
}

void TPageNominal::fillPageContainer(void) {
  TagList->Clear();
  TLabelInitStructure LabelInit;
  LabelInit.style = LabelsStyle::WIDTH_DINAMIC;
  LabelInit.Rect = { 10, 10, 10, 10 };
  LabelInit.focused = false;

  TagList->AddList({
      new TTagLine("���. ����", "U1/FLASH/SpdNom/", LabelInit),
      new TTagLine("���.��� ��", "U1/FLASH/CurNom/", LabelInit),
      new TTagLine("��� ������", "U1/FLASH/UrNom/", LabelInit),
      new TTagLine("UrefNulPrc", "U1/FLASH/UrefNulPrc/", LabelInit),
    });

}
