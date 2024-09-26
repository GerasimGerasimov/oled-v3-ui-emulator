#include "PageRegulatorSettings.h"
#include "TagLineScrollCaptionComment.h"
#include <FixedHeader.h>

TPageRegulatorSettings::TPageRegulatorSettings(std::string Name) : TPageBasicSettings(Name){
    TLabelInitStructure LabelInitH;
    LabelInitH.pOwner = Container;
    LabelInitH.caption = "Настройка регулят.";
    TFixedHeader* pHeader = new TFixedHeader(LabelInitH);
    delete Container->List[0];
    Container->List[0] = pHeader;
}

void TPageRegulatorSettings::fillPageContainer(void){
    TagList->Clear();
    TLabelInitStructure LabelInit;
    LabelInit.style = LabelsStyle::WIDTH_FIXED;
    LabelInit.Rect = {10, 10, 10, 70};
    LabelInit.focused = false;

    TagList->AddList({
        new TTagLineScrollCaptionComment("U1/FLASH/QpMax/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/QpMin/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/TKickStart/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/QpKickStart/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/KICK_START/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/UREG/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/StartTime/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/Ti/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/KReg/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/Td/", LabelInit),
        });
}