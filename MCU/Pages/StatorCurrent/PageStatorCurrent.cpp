#include "PageStatorCurrent.h"
#include "TagLine.h"
#include "FixedHeader.h"

//��� �������
TPageStatorCurrent::TPageStatorCurrent(std::string Name) : TPageBasicSettings(Name){
    TLabelInitStructure LabelInitH;
    LabelInitH.pOwner = Container;
    LabelInitH.caption = "��� �������";
    TFixedHeader* pHeader = new TFixedHeader(LabelInitH);
    delete Container->List[0];
    Container->List[0] = pHeader;
}

void TPageStatorCurrent::fillPageContainer(void){
    TagList->Clear();
    TLabelInitStructure LabelInit;
    LabelInit.style = LabelsStyle::WIDTH_DINAMIC;
    LabelInit.Rect = {10, 10, 10, 10};
    LabelInit.focused = false;

    TagList->AddList({
        new TTagLine("�����", "U1/RAM/None/", LabelInit),

        });
}
