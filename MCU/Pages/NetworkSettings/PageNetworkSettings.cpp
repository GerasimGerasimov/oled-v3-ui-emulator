#include "PageNetworkSettings.h"
#include "Router.h"
#include "TagLine.h"
#include <IniResources.h>
#include <FixedHeader.h>

void TPageNetworkSettings::view() {
    Container->view();
};

void TPageNetworkSettings::onOpen() {
    fillPageContainer();
    SubscriberID = HandlerSubscribers::set("U1/FLASH/", [this](TSlotHandlerArsg args) { SlotUpdate(args); });
}

void TPageNetworkSettings::startToClose() {
    HandlerSubscribers::remove("U1/FLASH/", SubscriberID);
    TagList->Clear();
    isOpen = false;
}


bool TPageNetworkSettings::ProcessMessage(TMessage* m) {
    TVisualObject* e = { nullptr };
    switch (m->Event) {
        case (u32)EventSrc::KEYBOARD: {
            switch (m->p1) {
                case (u32)KeyCodes::ESC:
                    TRouter::setTask({ false, "MainMenu", nullptr });
                    break;
                case (u32)KeyCodes::F1:
                    e = getSignalOfFocusedChild();
                    if (e) {
                        ISignal* p = IniResources::getSignalByTag(((TTagLine*)(e))->Tag);
                        TRouter::PageValueEditEntryData.backPage = Name;
                        TRouter::setTask({ false, "Help", p });
                    }
                    break;
                case (u32)KeyCodes::ENT:
                    e = getSignalOfFocusedChild();
                    if (e) {
                        TRouter::PageValueEditEntryData.tag = ((TTagLine*)(e))->Tag;
                        TRouter::PageValueEditEntryData.value = ((TTagLine*)(e))->Value->getCaption();
                        TRouter::PageValueEditEntryData.backPage = Name;
                        std::string EditPage = TRouter::selectEditPage(TRouter::PageValueEditEntryData.tag);
                        TRouter::setTask({ false, EditPage, nullptr });
                    }
                    break;
            }
        }
    }

    for (auto& element : List) {
        element->ProcessMessage(m);
    }
    return false;
};

TVisualObject* TPageNetworkSettings::getSignalOfFocusedChild() {
    for (auto& element : Container->List) {
        TVisualObject* e = element->getFocusedElement();
        TParameter* p = (e) ? (TParameter*) e->getDataSrc() : nullptr;
        if (p) return e;
    }
    return nullptr;
}

/*
; уставки связи - этот уарт выведен на разъем
p501=RS485_1_BPS/Baudrate/TPrmList/xF001/r2000.H/BPS//x01#9600/x02#19200/x03#57600/x04#115200/x04/
p502=RS485_1_DVA/Address/TByte/xF000/r2000.L/ /1/1//0/x01/
p503=RS485_1_PRTY/Parity/TPrmList/xF003/r2001.H/ //x00#None/x01#Odd/x02#Even/x00/
p504=RS485_1_STOP/Stop bits/TPrmList/xF002/r2001.L/ //x00#1bit/x01#0.5bit/x02#2bit/x03#1.5bit/x00/

p505=RS485_2_BPS/Baudrate/TPrmList/xF005/r2002.H/BPS//x01#9600/x02#19200/x03#57600/x04#115200/x04/
p506=RS485_2_DVA/Address/TByte/xF004/r2002.L/ /1/1//0/x01/
p507=RS485_2_PRTY/Parity/TPrmList/xF007/r2003.H/ //x00#None/x01#Odd/x02#Even/x00/
p508=RS485_2_STOP/Stop bits/TPrmList/xF006/r2003.L/ //x00#1bit/x01#0.5bit/x02#2bit/x03#1.5bit/x00/
*/

void TPageNetworkSettings::fillPageContainer(void) {
    TagList->Clear();
    TLabelInitStructure LabelInit;
    LabelInit.style = LabelsStyle::WIDTH_DINAMIC;
    LabelInit.Rect = { 10, 10, 10, 10 };
    LabelInit.focused = false;
    TagList->AddList({
        new TTagLine("DExS_PWR_LNK", "U1/RAM/DExS_PWR_LNK/", LabelInit),
        new TTagLine("tdir_Modbus_RS485", "U1/CD/tdir_Modbus_RS485/", LabelInit),
        new TTagLine("tdir_Modbus_option", "U1/CD/tdir_Modbus_option/", LabelInit),
        new TTagLine("Modbus_option_DVA", "U1/CD/Modbus_option_DVA/", LabelInit),
        new TTagLine("Modbus_option_BPS", "U1/CD/Modbus_option_BPS/", LabelInit),
        new TTagLine("Modbus_RS485_DVA", "U1/CD/Modbus_RS485_DVA/", LabelInit),
        new TTagLine("Modbus_RS485_BPS", "U1/CD/Modbus_RS485_BPS/", LabelInit),
        new TTagLine("COM1DVA", "U1/FLASH/COM1DVA/", LabelInit),
        new TTagLine("COM1BPS", "U1/FLASH/COM1BPS/", LabelInit),
        new TTagLine("COM2DVA", "U1/FLASH/COM2DVA/", LabelInit),
        new TTagLine("COM2BPS", "U1/FLASH/COM2BPS/", LabelInit),
        new TTagLine("COM3DVA", "U1/FLASH/COM3DVA/", LabelInit),
        new TTagLine("COM3BPS", "U1/FLASH/COM3BPS/", LabelInit),
        new TTagLine("COM4_ADR", "U1/FLASH-ICM/COM4_ADR/", LabelInit),
        new TTagLine("COM4_BPS", "U1/FLASH-ICM/COM4_BPS/", LabelInit),
        //new TTagLine("iCM_IP_ADDR", "U1/FLASH-ICM/iCM_IP_ADDR/", LabelInit),

    });
}

TPageNetworkSettings::TPageNetworkSettings(std::string Name)
    :TPage(Name) {
    TVerticalContainerProps props = { false };
    Container = new TVerticalContainer(props, {});

    TLabelInitStructure LabelInit;
    LabelInit.pOwner = Container;
    LabelInit.caption = "Настройки связи";
    TFixedHeader* pHeader = new TFixedHeader(LabelInit);
    Container->Add(pHeader);

    props = { true };
    TagList = new TVerticalContainer(props, {});
    TagList->ElementRect = { 0, 0,
                            (u16)(VIEW_PORT_MAX_HEIGHT - pHeader->getHeight() - 1),
                            VIEW_PORT_MAX_WIDTH };
    Container->Add(TagList);

    AddList({ Container });
};

void TPageNetworkSettings::SlotUpdate(TSlotHandlerArsg args) {
    for (auto& e : TagList->List) {
        TTagLine* tag = (TTagLine*)e;
        TParameter* p = (TParameter*)tag->getDataSrc();
        tag->Value->setCaption(p->getValue(args, ""));
    }
    Msg::send_message((u32)EventSrc::REPAINT, 0, 0);
}

TPageNetworkSettings::~TPageNetworkSettings() {
    TagList->Clear();
    Container->Clear();
    delete Container;
};
