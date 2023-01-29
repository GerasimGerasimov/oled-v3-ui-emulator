#include "PagePanelSettings.h"
#include "Router.h"
#include "TagLine.h"
#include <IniResources.h>
#include <FixedHeader.h>

/*TODO �� ��� ��� ��� �������� ������ �� FLASH ������ ���������� ��?!
��� �� �� ��� ��������������� ��� ��������� � ini-�����
���� ������ ��� ������, ���� �� ������� � ��� �������.
���� ������������ ������� ��������� �� �������� ��� �� �� ������ � COM-������*/

void TPagePanelSettings::view() {
    Container->view();
};

void TPagePanelSettings::onOpen() {
    fillPageContainer();
    //SubscriberID = HandlerSubscribers::set("U1/FLASH/", [this](TSlotHandlerArsg args) { SlotUpdate(args); });
}

void TPagePanelSettings::startToClose() {
    //HandlerSubscribers::remove("U1/FLASH/", SubscriberID);
    TagList->Clear();
    isOpen = false;
}


bool TPagePanelSettings::ProcessMessage(TMessage* m) {
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

TVisualObject* TPagePanelSettings::getSignalOfFocusedChild() {
    for (auto& element : Container->List) {
        TVisualObject* e = element->getFocusedElement();
        TParameter* p = (e) ? (TParameter*) e->getDataSrc() : nullptr;
        if (p) return e;
    }
    return nullptr;
}

/*
; ������� ����� - ���� ���� ������� �� ������
p501=RS485_1_BPS/Baudrate/TPrmList/xF001/r2000.H/BPS//x01#9600/x02#19200/x03#57600/x04#115200/x04/
p502=RS485_1_DVA/Address/TByte/xF000/r2000.L/ /1/1//0/x01/
p503=RS485_1_PRTY/Parity/TPrmList/xF003/r2001.H/ //x00#None/x01#Odd/x02#Even/x00/
p504=RS485_1_STOP/Stop bits/TPrmList/xF002/r2001.L/ //x00#1bit/x01#0.5bit/x02#2bit/x03#1.5bit/x00/

p505=RS485_2_BPS/Baudrate/TPrmList/xF005/r2002.H/BPS//x01#9600/x02#19200/x03#57600/x04#115200/x04/
p506=RS485_2_DVA/Address/TByte/xF004/r2002.L/ /1/1//0/x01/
p507=RS485_2_PRTY/Parity/TPrmList/xF007/r2003.H/ //x00#None/x01#Odd/x02#Even/x00/
p508=RS485_2_STOP/Stop bits/TPrmList/xF006/r2003.L/ //x00#1bit/x01#0.5bit/x02#2bit/x03#1.5bit/x00/
*/

void TPagePanelSettings::fillPageContainer(void) {
    TagList->Clear();
    TLabelInitStructure LabelInit;
    LabelInit.style = LabelsStyle::WIDTH_DINAMIC;
    LabelInit.Rect = { 10, 10, 10, 10 };
    LabelInit.focused = false;
    TParameter* DataSrc = (TParameter*)IniResources::getSignalByTag("SLF/FLASH/ModbusSlaveU1_BPS/");
    TagList->AddList({
        new TTagLine("#1BPS", "SLF/FLASH/ModbusSlaveU1_BPS/", LabelInit),
        new TTagLine("#1DVA", "SLF/FLASH/ModbusSlaveU1_DVA/", LabelInit),
        new TTagLine("#1PRTY", "SLF/FLASH/ModbusSlaveU1_PRTY/", LabelInit),
        new TTagLine("#1STOP", "SLF/FLASH/ModbusSlaveU1_STOP/", LabelInit),
    });
}

TPagePanelSettings::TPagePanelSettings(std::string Name)
    :TPage(Name) {
    TVerticalContainerProps props = { false };
    Container = new TVerticalContainer(props, {});

    TLabelInitStructure LabelInit;
    LabelInit.pOwner = Container;
    LabelInit.caption = "��������� ������";
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

void TPagePanelSettings::SlotUpdate(TSlotHandlerArsg args) {
    /*
    for (auto& e : TagList->List) {
        TTagLine* tag = (TTagLine*)e;
        TParameter* p = (TParameter*)tag->getDataSrc();
        tag->Value->setCaption(p->getValue(args, ""));
    }
    Msg::send_message((u32)EventSrc::REPAINT, 0, 0);
    */
}

TPagePanelSettings::~TPagePanelSettings() {
    TagList->Clear();
    Container->Clear();
    delete Container;
};
