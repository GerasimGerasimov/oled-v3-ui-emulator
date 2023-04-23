#include "PageHome.h"
#include "Router.h"
#include "TagLine.h"
#include <IniResources.h>
#include <AppModbusSlave.h>
#include <utils.h>

void TPageHome::view() {
    TagList->view();
};

void TPageHome::onOpen() {
    fillPageContainer();
    SubscriberID = HandlerSubscribers::set("U1/RAM/", [this](TSlotHandlerArsg args) { SlotUpdate(args); });
}

void TPageHome::startToClose() {
    HandlerSubscribers::remove("U1/RAM/", SubscriberID);
    TagList->Clear();
    isOpen = false;
}

static const float stepIrefFirst = 1.0f;
static const float stepIrefAuto = 5.0f;
static const float minIref = 20.0f;
static const float maxIref = 1000.0f;

bool TPageHome::ProcessMessage(TMessage* m) {
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
                TRouter::setTask({ false, "EditValue", nullptr });
            }
            break;
        case (u32)KeyCodes::Left:
            //����� ���� � ����������� ��� ����������� ������� ��� �������������� ������
            decreaseIref((m->p2 == (u32)KeyPressFeature::AutoRepeat) ? stepIrefAuto : stepIrefFirst);
            break;
        case (u32)KeyCodes::Right:
            increaseIref((m->p2 == (u32)KeyPressFeature::AutoRepeat) ? stepIrefAuto : stepIrefFirst);
            break;
        }
    }
    }

    for (auto& element : List) {
        element->ProcessMessage(m);
    }
    return false;
};

TTagLine* getIrefPlaceHolder(TComponentsContainer* Src) {
    const std::string tag = "U1/RAM/Iref/";
    TTagLine* res = nullptr;
    for (auto& e : Src->List) {
        if (e->ComponentName() == "TTagLine") {
            TTagLine* t = (TTagLine*)e;
            if (t->Tag == tag) {
                res = t;
                break;
            }
        }
    }
    return res;
}

void TPageHome::decreaseIref(float step) {
    if (cmdSendInProcess) return;
    /*�������� ������� �������� Iref, ������� �� ���� 1A ��� 5� (� �����������
     ����������� ��� ������� ��� �������������� ������)� �������� �� EFi
    �������� ����� ���� �� �������� � "**.**" ����� ��� �����, ������
    1) �������� �������� 2) �������� ��� �������� 3) ���������� ��� ��� ����������
    4) ����������  � ������ 5) ��������� */
    TTagLine* TagLine = getIrefPlaceHolder(TagList);

    if (TagLine) {
        std::string value = TagLine->Value->getCaption();
        try {
            float f = std::stof(value);
            f = ((f - step) < minIref)
                ? minIref
                : f -= step;
            value = Utils::getValueAsFormatStr(f, "%f");
        }
        catch (...) {
            //����� ����, ������ ��� ������ �� ��������������� � float
            return;
        };
        sendCmd(value);
    }
}

void TPageHome::increaseIref(float step) {
    if (cmdSendInProcess) return;
    TTagLine* TagLine = getIrefPlaceHolder(TagList);

    if (TagLine) {
        std::string value = TagLine->Value->getCaption();
        try {
            float f = std::stof(value);
            f = ((f + step) > maxIref)
                ? maxIref
                : f += step;
            value = Utils::getValueAsFormatStr(f, "%f");
        }
        catch (...) {
            //����� ����, ������ ��� ������ �� ��������������� � float
            return;
        };
        sendCmd(value);
    }
}

void TPageHome::sendCmd(std::string& value) {
    std::string tag = "U1/FLASH/Iref/";
    /*TODO ������� ������ ���� ���������� Iref
      ���� � RAM �� ���� ������������ �������� Efi ��� ��� � NormalMode ������ ������� ��� �� ����� ������� � RAM
           � ������� �� ����� ������ ������� �� ������ �������� �� �����
      ���� Flash - ����� ������� �������� �� ����� ������ (������������ � ����� ������� � �� ���� �������� � ��������� � ������������ � RAM)
           �� ��� ���������, �� ��� ���� �� �������, ����� �������� � �������� Flash
    */
    TryCount = 1;
    cmdSendInProcess = true;
    ModbusSlave::setValue(tag, value, [this](Slot* slot, u8* reply) { SlotUpdate(slot, reply); });
}

void TPageHome::SlotUpdate(Slot* slot, u8* reply) {
    if (slot->RespondLenghtOrErrorCode) {
        slot->Flags |= (u16)SlotStateFlags::SKIP_SLOT;
        cmdSendInProcess = false;
    }
    else {
        if (TryCount)
            TryCount--;
        else {
            slot->Flags |= (u16)SlotStateFlags::SKIP_SLOT;
            cmdSendInProcess = false;
        }
    }
}

TVisualObject* TPageHome::getSignalOfFocusedChild() {
    for (auto& element : List) {
        TVisualObject* e = element->getFocusedElement();
        TParameter* p = (e) ? (TParameter*)e->getDataSrc() : nullptr;
        if (p) return e;
    }
    return nullptr;
}

void TPageHome::fillPageContainer(void) {
    TagList->Clear();
    TLabelInitStructure LabelInit;
    LabelInit.style = LabelsStyle::WIDTH_DINAMIC;
    LabelInit.Rect = { 10, 10, 10, 10 };
    LabelInit.focused = false;
    TagList->AddList({
        new TTagLine("Uref", "U1/RAM/Uref/", LabelInit),
        new TTagLine("Iref", "U1/RAM/Iref/", LabelInit),
        new TTagLine("UoutAve", "U1/RAM/UoutAve/", LabelInit),
        new TTagLine("IoutAve", "U1/RAM/IoutAve/", LabelInit),
        new TTagLine("SpReq", "U1/RAM/SparkFrq/", LabelInit),
        new TTagLine("Out", "U1/RAM/Out/", LabelInit),
        });
}

TPageHome::TPageHome(std::string Name)
    :TPage(Name)
    , cmdSendInProcess(false)
    , TryCount(3) {
    TVerticalContainerProps props = { false };
    TagList = new TVerticalContainer(props, {});
    AddList({ TagList });
};

void TPageHome::SlotUpdate(TSlotHandlerArsg args) {
    for (auto& e : TagList->List) {
        TTagLine* tag = (TTagLine*)e;
        TParameter* p = (TParameter*)tag->getDataSrc();
        tag->Value->setCaption(p->getValue(args, ""));
    }
    Msg::send_message((u32)EventSrc::REPAINT, 0, 0);
}

TPageHome::~TPageHome() {
    TagList->Clear();
    delete TagList;
};
