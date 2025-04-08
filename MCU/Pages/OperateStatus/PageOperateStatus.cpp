#include "PageOperateStatus.h"
#include "Router.h"
#include <IniResources.h>
#include "TagLineScrollCaptionComment.h"
#include <map>
#include <AppModbusSlave.h>

void TPageOperateStatus::view() {
    Container->view();
};

void TPageOperateStatus::onOpen() {
    SubscriberID = HandlerSubscribers::set("U1/RAM/", [this](TSlotHandlerArsg args) { SlotU1RAMUpdate(args); });
}

void TPageOperateStatus::startToClose() {
    HandlerSubscribers::remove("U1/RAM/", SubscriberID);
    isOpen = false;
}

bool TPageOperateStatus::ProcessMessage(TMessage* m) {
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
                        TRouter::PageValueEditEntryData.backPage = Name;
                        ISignal* p = IniResources::getSignalByTag(((TTagLine*)(e))->Tag);
                        TRouter::setTask({ false, "Help", p });
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

static const std::string CMD_STOP = "1000";
static const std::string CMD_START = "1111";
//static const std::string CMD_TEST = "5313";

static const std::map <std::string, std::string> CmdBySignalName = {
    {"Run", CMD_START},
    {"stop", CMD_STOP},
};

void TPageOperateStatus::sendModeCmd(ISignal* signal) {
    std::string name = signal->getName();
    if (CmdBySignalName.count(name)) {
        sendCmd((std::string&)CmdBySignalName.at(name));
    }
}

void TPageOperateStatus::sendCmd(std::string& code) {
    std::string cmd = "U1/RAM/RefCmd/";
    TryCount = 3;
    cmdSendInProcess = true;
    ModbusSlave::setValue(cmd, code, [this](Slot* slot, u8* reply) { SlotUpdate(slot, reply); });
}

void TPageOperateStatus::SlotUpdate(Slot* slot, u8* reply) {
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

TVisualObject* TPageOperateStatus::getSignalOfFocusedChild() {
    for (auto& element : List) {
        TVisualObject* e = element->getFocusedElement();
        TParameter* p = (e) ? (TParameter*) e->getDataSrc() : nullptr;
        if (p) return e;
    }
    return nullptr;
}

TPageOperateStatus::TPageOperateStatus(std::string Name)
    :TPage(Name)
    , SubscriberID(0)
    , cmdSendInProcess(false)
    , TryCount(3) {
    TVerticalContainerProps props = { true };
    TLabelInitStructure LabelInit;
    LabelInit.style = LabelsStyle::WIDTH_FIXED;
    LabelInit.Rect = { 10, 10, 10, 70 };
    LabelInit.focused = false;

    Container = new TVerticalContainer(props, {
        new TTagLine("����������", "U1/RAM/Ready/", LabelInit),
        new TTagLine("������", "U1/RAM/Run/", LabelInit),
        new TTagLineScrollCaptionComment("U1/RAM/OutOk/", LabelInit),
        new TTagLineScrollCaptionComment("U1/RAM/Fan2/", LabelInit),
        new TTagLineScrollCaptionComment("U1/RAM/SoftStart/", LabelInit),
        });
    
    Container->FocusedLine = 0;

    AddList({ Container });
};

void TPageOperateStatus::SlotU1RAMUpdate(TSlotHandlerArsg args) {
    for (auto& e : Container->List) {
        TTagLine* tag = (TTagLine*)e;
        TParameter* p = (TParameter*)tag->getDataSrc();
        tag->Value->setCaption(p->getValue(args, "%.0f"));
    };
    Msg::send_message((u32)EventSrc::REPAINT, 0, 0);
}

TPageOperateStatus::~TPageOperateStatus() {
};
