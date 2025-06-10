#include "PagePowerSettings.h"
#include "Router.h"
#include "TagLine.h"
#include "TagLineScrollCaptionComment.h"
#include <IniResources.h>
#include <FixedHeader.h>
#include "PageBasicSettings.h"

void TPagePowerSettings::fillPageContainer(void) {
    TagList->Clear();
    TLabelInitStructure LabelInit;
    LabelInit.style = LabelsStyle::WIDTH_DINAMIC;
    LabelInit.Rect = { 10, 10, 10, 10};
    LabelInit.focused = false;

    TagList->AddList({
        new TTagLine("UmaxSpRect", "U1/FLASH/UmaxSpRect/", LabelInit),
        new TTagLine("UminSpRect", "U1/FLASH/UminSpRect/", LabelInit),
        new TTagLine("FmaxSpRect", "U1/FLASH/FmaxSpRect/", LabelInit),
        new TTagLine("FminSpRect", "U1/FLASH/FminSpRect/", LabelInit),
        new TTagLine("SUPPLFltT", "U1/FLASH/SUPPLFltTime/", LabelInit)
        });
}

TPagePowerSettings::TPagePowerSettings(std::string Name) :TPageBasicSettings(Name) {
    TLabelInitStructure LabelInitH;
    LabelInitH.pOwner = Container;
    LabelInitH.caption = "Уставки питания";
    TFixedHeader* pHeader = new TFixedHeader(LabelInitH);
    delete Container->List[0];
    Container->List[0] = pHeader;
};
