#include "PageAlarms.h"
#include "Router.h"
#include <utils.h>
#include <FixedHeader.h>
#include <FixedFooter.h>
#include "Alarms.h"
#include "LinkLabel.h"
#include "TVerticalContainer.h"

void TPageAlarms::onOpen() {
    Container->Clear();
    fillPageContainer();
}

void TPageAlarms::startToClose() {

}

void TPageAlarms::view() {
    Container->view();
};

void TPageAlarms::clear() {
}

bool TPageAlarms::ProcessMessage(TMessage* m) {
    switch (m->Event) {
        case (u32)EventSrc::KEYBOARD: {
            switch (m->p1) {
                case (u32)KeyCodes::ESC:
                    TRouter::setTask({ false, "Home", nullptr });
                    break;
            }
        }
    }

    for (auto& element : List) {
        element->ProcessMessage(m);
    }
    return false;
};

void TPageAlarms::fillPageContainer(void) {
    TLabelInitStructure LabelInit;

    LabelInit.pOwner = Container;
    LabelInit.caption = "Аварии";
    TFixedHeader* pHeader = new TFixedHeader(LabelInit);
    Container->Add(pHeader);

    TVerticalContainer* pLabels = new TVerticalContainer({});
    pLabels->ElementRect = { 0, 0,
                                (u16)(VIEW_PORT_MAX_HEIGHT - pHeader->getHeight() - 1),
                                VIEW_PORT_MAX_WIDTH };
    Container->Add(pLabels);
    
    LabelInit.Rect = {0, 0, 0, VIEW_PORT_MAX_WIDTH };

    LabelInit.style = LabelsStyle::WIDTH_DINAMIC;
    for (auto& e : Alarms::Tags) {
        if (Alarms::isTagAlarmed(e.second)) {
            TBit* p = e.second.pBit;
            LabelInit.caption = p->getComment();
            TLinkLabel* pLabel = new TLinkLabel(LabelInit.caption, "Home", LabelInit);
            pLabels->Add(pLabel);
        }
    }
}

TPageAlarms::TPageAlarms(std::string Name)
    :TPage(Name) {
    Container = new TComponentListVertical({});
    AddList({ Container });
};

TPageAlarms::~TPageAlarms() {
};
