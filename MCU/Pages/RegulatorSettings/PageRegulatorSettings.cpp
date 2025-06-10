#include "PageRegulatorSettings.h"
#include "Router.h"
#include "TagLine.h"
#include "TagLineScrollCaptionComment.h"
#include <IniResources.h>
#include <FixedHeader.h>

void TPageRegulatorSettings::fillPageContainer(void) {
    TagList->Clear();
    TLabelInitStructure LabelInit;
    LabelInit.style = LabelsStyle::WIDTH_DINAMIC;
    LabelInit.Rect = { 10, 10, 10, 10 };
    LabelInit.focused = false;

    TagList->AddList({
        new TTagLine("Ti", "U1/FLASH/Ti/", LabelInit),
        new TTagLine("Ku", "U1/FLASH/Ku/", LabelInit),
        new TTagLine("Td", "U1/FLASH/Td/", LabelInit)
        });
}

TPageRegulatorSettings::TPageRegulatorSettings(std::string Name) :TPageBasicSettings(Name) {
    TLabelInitStructure LabelInitH;
    LabelInitH.pOwner = Container;
    LabelInitH.caption = "Уставки регулятора";
    TFixedHeader* pHeader = new TFixedHeader(LabelInitH);
    delete Container->List[0];
    Container->List[0] = pHeader;
};