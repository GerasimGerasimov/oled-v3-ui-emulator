#include "PageConnectionSetting.h"
#include <FixedHeader.h>
#include "Router.h"
#include "TagLine.h"

TPageConnectionSetting::TPageConnectionSetting(std::string Name) : TPageBasicSettings(Name) {
    TLabelInitStructure LabelInitH;
    LabelInitH.pOwner = Container;
    LabelInitH.caption = "Уставки связи";
    TFixedHeader* pHeader = new TFixedHeader(LabelInitH);
    delete Container->List[0];
    Container->List[0] = pHeader;
}

void TPageConnectionSetting::fillPageContainer() {
    TagList->Clear();
    TLabelInitStructure LabelInit;
    LabelInit.style = LabelsStyle::WIDTH_FIXED;
    LabelInit.Rect = { 10, 10, 10, 80 };
    LabelInit.focused = false;
    TagList->AddList({
        new TTagLine("RS485OPT_BPS", "U1/FLASH/RS485OPT_BPS/", LabelInit),
        new TTagLine("RS485OPT_DVA", "U1/FLASH/RS485OPT_DVA/", LabelInit)
        });
}