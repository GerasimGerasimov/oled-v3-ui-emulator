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
        new TTagLine("USB_1_Baudrate", "U1/FLASH/RS485_USB_1_Baudrate/", LabelInit),
        new TTagLine("USB_1_Address", "U1/FLASH/RS485_USB_1_Address/", LabelInit),
        new TTagLine("USB_1_Parity", "U1/FLASH/RS485_USB_1_Parity/", LabelInit),
        new TTagLine("USB_1_STOP", "U1/FLASH/RS485_USB_1_STOP/", LabelInit)
        });
}