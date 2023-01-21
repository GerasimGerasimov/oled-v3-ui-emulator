#include "PageParameterListEdit.h"
#include "Router.h"
#include <IniResources.h>
#include <AppModbusSlave.h>
#include "RAMdata.h"
#include "Label.h"
#include "TPrmList.h"

void TPageParameterListEdit::view() {
    Container->view();
};

void TPageParameterListEdit::onOpen() {
    tag = TRouter::PageValueEditEntryData.tag;
    p = (TParameter*)IniResources::getSignalByTag(tag);
    fillPageContainer();
}

void TPageParameterListEdit::startToClose() {
    TagList->Clear();
    isOpen = false;
}

bool TPageParameterListEdit::ProcessMessage(TMessage* m) {
    for (auto& element : List) {
       element->ProcessMessage(m);
    }

    switch (m->Event) {
        case (u32)EventSrc::KEYBOARD: {
            switch (m->p1) {
                case (u32)KeyCodes::ESC:
                    TRouter::setTask({ false, "Home", nullptr });
                    return true;
                case (u32)KeyCodes::ENT:
                    sendValue();
                    return true;
                }
        }
    }
    if (isDataSent) {
        isDataSent = false;
        TRouter::setTask({ false, "Home", nullptr });
    }
    return false;
};

void TPageParameterListEdit::SlotUpdate(Slot& slot, u8* reply) {
    /*
    slot.Flags |= (u16)SlotStateFlags::SKIP_SLOT;
    isDataSent = true;
    */
}

void TPageParameterListEdit::sendValue(void) {
    /*
    std::string value = pEdit->getValue();
    if (ModbusSlave::setValue(tag, value, [this](Slot& slot, u8* reply) { SlotUpdate(slot, reply);})) {

    }
    else {
        isDataSent = true;
    }
    */
}

void TPageParameterListEdit::fillPageContainer(void) {
    TagList->Clear();
    pHeader->setCaption(p->getName());
    TLabelInitStructure LabelInit;
    LabelInit.style = LabelsStyle::WIDTH_DINAMIC;
    LabelInit.Rect = { 10, 10, 10, 10 };
    LabelInit.focused = false;

    TPrmList* prm = (TPrmList*)p;
    std::vector<std::string> ParamList = prm->getList();

    std::vector <TVisualObject*> Source = {};
    for (auto& e : ParamList) {
        LabelInit.caption = e;
        TLabel* lb = new TLabel(LabelInit);
        TagList->List.push_back(lb);
    }

    //TagList->AddList({
        //new TTagLine("#1BPS", "U1/FLASH/RS485_1_BPS/", LabelInit),
    //    });
}

TPageParameterListEdit::TPageParameterListEdit(std::string Name)
    :TPage(Name)
    , p(nullptr) {
    TVerticalContainerProps props = { false };
    Container = new TVerticalContainer(props, {});

    TLabelInitStructure LabelInit;
    LabelInit.pOwner = Container;
    LabelInit.caption = "ParamListEdit";
    pHeader = new TFixedHeader(LabelInit);
    Container->Add(pHeader);

    props = { true };
    TagList = new TVerticalContainer(props, {});
    TagList->ElementRect = { 0, 0,
                            (u16)(VIEW_PORT_MAX_HEIGHT - pHeader->getHeight() - 1),
                            VIEW_PORT_MAX_WIDTH };
    Container->Add(TagList);

    AddList({ Container });
};

TPageParameterListEdit::~TPageParameterListEdit() {
    TagList->Clear();
    Container->Clear();
    delete Container;
};
