#include "PageCosSetting.h"
#include "TagLine.h"
#include "FixedHeader.h"

//cos ���������
TPageCosSetting::TPageCosSetting(std::string Name) : TPageBasicSettings(Name){
    TLabelInitStructure LabelInitH;
    LabelInitH.pOwner = Container;
    LabelInitH.caption = "cos ���������";
    TFixedHeader* pHeader = new TFixedHeader(LabelInitH);
    delete Container->List[0];
    Container->List[0] = pHeader;
}

void TPageCosSetting::fillPageContainer(void){
    TagList->Clear();
    TLabelInitStructure LabelInit;
    LabelInit.style = LabelsStyle::WIDTH_DINAMIC;
    LabelInit.Rect = {10, 10, 10, 10};
    LabelInit.focused = false;

    TagList->AddList({
        new TTagLine("�����", "U1/RAM/None/", LabelInit),

        });
}
