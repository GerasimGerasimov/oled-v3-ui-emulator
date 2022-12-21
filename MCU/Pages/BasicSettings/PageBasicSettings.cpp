#include "PageBasicSettings.h"
#include "Router.h"
#include "TagLine.h"
#include <IniResources.h>
#include <FixedHeader.h>

void TPageBasicSettings::view() {
    Container->view();
};

void TPageBasicSettings::onOpen() {
    fillPageContainer();
    SubscriberID = HandlerSubscribers::set("U1/FLASH/", [this](TSlotHandlerArsg args) { SlotUpdate(args); });
}

void TPageBasicSettings::startToClose() {
    HandlerSubscribers::remove("U1/FLASH/", SubscriberID);
    TagList->Clear();
    isOpen = false;
}

bool TPageBasicSettings::ProcessMessage(TMessage* m) {
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
                        TRouter::setTask({ false, "Help", p });
                    }
                    break;
                case (u32)KeyCodes::ENT:
                    e = getSignalOfFocusedChild();
                    if (e) {
                        TRouter::PageValueEditEntryData.tag = ((TTagLine*)(e))->Tag;
                        TRouter::PageValueEditEntryData.value = ((TTagLine*)(e))->Value->getCaption();
                        TRouter::setTask({ false, "EditValue", nullptr });
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

TVisualObject* TPageBasicSettings::getSignalOfFocusedChild() {
    for (auto& element : Container->List) {
        TVisualObject* e = element->getFocusedElement();
        TParameter* p = (e) ? (TParameter*) e->getDataSrc() : nullptr;
        if (p) return e;
    }
    return nullptr;
}

/*
;�������� ������� ������
p603=Uref/���������� �������/TWORD/xF00E/r2007/kV/FracHundScale/2//0/x1B58/
p604=Iref/��� �������/TWORD/xF010/r2008/mA/FracDecScale/2//0/x03E8/
p605=dOutRun/������������ �������� ���������� ������� ���������� ���������������� � ������� ������/TWORD/xF012/r2009/%\s/IntegerScale/2//0/x0002/
p606=dOutStop/������������ �������� ����� ������� ���������� ���������������� ��� ���������/TWORD/xF014/r200A/%\s/IntegerScale/2//0/x000A/
p607=dOutAfterSpark/������������ �������� ���������� ������� ���������� ���������������� ����� �����/TWORD/xF016/r200B/%\s/IntegerScale/2//0/x03E8/
p608=tHoldAfterSpark/���������� ����� ����� ������������� �����/TWORD/xF018/r200C/s/FracHundScale/2//0/x0003/
p609=KsparkLength/����������� ���������� �� ������������� ��������� �������/TWORD/xF01A/r200D/%\us/FracDecThousScale/2//0/x0064/
p610=KsparkFrq/����������� ���������� �� ������� ����/TWORD/xF01C/r200E/kV\pcs/FracThousScale/2//0/x0000/
p611=Ku/����������� ���������� �� ����������/TWORD/xF01E/r200F/ /FracThousScale/2//0/x000A/
p612=Ki/����������� ���������� �� ����/TWORD/xF020/r2010/ /FracThousScale/2//0/x00C8/
p613=tShakerPeriod1/������ ������� ������������� 1/TWORD/xF022/r2011/s/FracDecScale/2//0/xFFFF/
p614=tShakerPulse1/������ �������� ������� ������������� 1/TWORD/xF024/r2012/s/FracDecScale/2//0/x0001/
p615=tShakerPeriod2/������ ������� ������������� 2/TWORD/xF026/r2013/s/FracDecScale/2//0/xFFFF/
p616=tShakerPulse2/������ �������� ������� ������������� 2/TWORD/xF028/r2014/s/FracDecScale/2//0/x0001/
p617=AlphaMin/����������� ���� ���������� ����������� ����������������/TWORD/xF02A/r2015/grad/FracHundScale/2//0/x01F4/
p618=AlphaMax/������������ ���� ���������� ����������� ����������������/TWORD/xF02C/r2016/grad/FracHundScale/2//0/x4268/
*/

void TPageBasicSettings::fillPageContainer(void) {
    TagList->Clear();
    TLabelInitStructure LabelInit;
    LabelInit.style = LabelsStyle::WIDTH_DINAMIC;
    LabelInit.Rect = { 10, 10, 10, 10 };
    LabelInit.focused = false;
    TagList->AddList({
        new TTagLine("Uref", "U1/FLASH/Uref/", LabelInit),
        new TTagLine("Iref", "U1/FLASH/Iref/", LabelInit),
        new TTagLine("dOutRun", "U1/FLASH/dOutRun/", LabelInit),
        new TTagLine("dOutStop", "U1/FLASH/dOutStop/", LabelInit),
        new TTagLine("dOutASprk", "U1/FLASH/dOutAfterSpark/", LabelInit),
        new TTagLine("tHldASprk", "U1/FLASH/tHoldAfterSpark/", LabelInit),
        new TTagLine("KsprkLen", "U1/FLASH/KsparkLength/", LabelInit),
        new TTagLine("KsprkFrq", "U1/FLASH/KsparkFrq/", LabelInit),
        new TTagLine("Ku", "U1/FLASH/Ku/", LabelInit),
        new TTagLine("Ki", "U1/FLASH/Ki/", LabelInit),
        new TTagLine("tShPer1", "U1/FLASH/tShakerPeriod1/", LabelInit),
        new TTagLine("tShPause1", "U1/FLASH/tShakerPulse1/", LabelInit),
        new TTagLine("tShPer2", "U1/FLASH/tShakerPeriod2/", LabelInit),
        new TTagLine("AMin", "U1/FLASH/AlphaMin/", LabelInit),
        new TTagLine("AMax", "U1/FLASH/AlphaMax/", LabelInit),
    });
}

TPageBasicSettings::TPageBasicSettings(std::string Name)
    :TPage(Name) {
    TVerticalContainerProps props = { false };
    Container = new TVerticalContainer(props, {});

    TLabelInitStructure LabelInit;
    LabelInit.pOwner = Container;
    LabelInit.caption = "�������� �������";
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

void TPageBasicSettings::SlotUpdate(TSlotHandlerArsg args) {
    for (auto& e : TagList->List) {
        TTagLine* tag = (TTagLine*)e;
        TParameter* p = (TParameter*)tag->getDataSrc();
        tag->Value->setCaption(p->getValue(args, "%.0f"));/*TODO ������ ��� ������� ��������� ������� � ��� TLabel*/
    }
    Msg::send_message((u32)EventSrc::REPAINT, 0, 0);
}

TPageBasicSettings::~TPageBasicSettings() {
};
