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
    LabelInit.style = LabelsStyle::WIDTH_FIXED;
    LabelInit.Rect = { 10, 10, 10, 80 };
    LabelInit.focused = false;
    TagList->AddList({
        new TTagLine("RS485BD", "U1/FLASH/RS485_USB_1_Baudrate/", LabelInit),
        new TTagLine("RS485ADDR", "U1/FLASH/RS485_USB_1_Address/", LabelInit),
        new TTagLine("RS4853BD", "U1/FLASH/RS485_3_Baudrate/", LabelInit),
        new TTagLine("RS4853ADDR", "U1/FLASH/RS485_3_Address/", LabelInit)
        });
}