#include "PagePanelSettingsEFI.h"
#include "Router.h"
#include "TagLine.h"
#include "TagLineScrollCaptionComment.h"
#include <IniResources.h>
#include <FixedHeader.h>
#include "PageBasicSettings.h"

void TPagePanelSettingsEFI::fillPageContainer(void) {
    TagList->Clear();
    TLabelInitStructure LabelInit;
    LabelInit.style = LabelsStyle::WIDTH_DINAMIC;
    LabelInit.Rect = { 10, 10, 10, 10 };
    LabelInit.focused = false;

    TagList->AddList({
        new TTagLine("#1BPS", "U1/FLASH/RS485_1_BPS/", LabelInit),
        new TTagLine("#1ADR", "U1/FLASH/RS485_1_DVA/", LabelInit),
        new TTagLine("#1PRT", "U1/FLASH/RS485_1_PRTY/", LabelInit),
        new TTagLine("#1STP", "U1/FLASH/RS485_1_STOP/", LabelInit),
        new TTagLine("#2BPS", "U1/FLASH/RS485_2_BPS/", LabelInit),
        new TTagLine("#2ADR", "U1/FLASH/RS485_2_DVA/", LabelInit),
        new TTagLine("#2PRT", "U1/FLASH/RS485_2_PRTY/", LabelInit),
        new TTagLine("#2STP", "U1/FLASH/RS485_2_STOP/", LabelInit)
        });
}

TPagePanelSettingsEFI::TPagePanelSettingsEFI(std::string Name) :TPageBasicSettings(Name) {
    TLabelInitStructure LabelInitH;
    LabelInitH.pOwner = Container;
    LabelInitH.caption = "Встряхиватели";
    TFixedHeader* pHeader = new TFixedHeader(LabelInitH);
    delete Container->List[0];
    Container->List[0] = pHeader;
};