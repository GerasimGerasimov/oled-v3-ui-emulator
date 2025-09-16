#include "PageCommunicationSettings.h"
#include <FixedHeader.h>
#include "Router.h"
#include "TagLine.h"

TPageCommunicationSettings::TPageCommunicationSettings(std::string Name) : TPageBasicSettings(Name) {
    TLabelInitStructure LabelInitH;
    LabelInitH.pOwner = Container;
    LabelInitH.caption = "Уставки связи";
    TFixedHeader* pHeader = new TFixedHeader(LabelInitH);
    delete Container->List[0];
    Container->List[0] = pHeader;
}

void TPageCommunicationSettings::fillPageContainer() {
    TagList->Clear();
    TLabelInitStructure LabelInit;
    LabelInit.style = LabelsStyle::WIDTH_DINAMIC;
    LabelInit.Rect = { 10, 10, 10, 10 };
    LabelInit.focused = false;
    TagList->AddList({
        new TTagLine("RS485_BPS", "U1/FLASH/RS485_BPS/", LabelInit),
        new TTagLine("RS485_DVA", "U1/FLASH/RS485_DVA/", LabelInit),
        new TTagLine("USB_BPS", "U1/FLASH/USB_BPS/", LabelInit),
        new TTagLine("USB_DVA", "U1/FLASH/USB_DVA/", LabelInit)
        });
}