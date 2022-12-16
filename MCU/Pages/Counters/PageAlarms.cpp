#include "PageAlarms.h"
#include "Router.h"
#include <utils.h>
#include <FixedHeader.h>
#include <FixedFooter.h>
#include "Alarms.h"
#include "LinkLabel.h"
#include "TVerticalContainer.h"

static u16 count;

void TPageAlarms::onOpen() {
    Container->Clear();
    fillPageContainer();
    //count++;
    //std::string newCaption = Utils::UnSignedintToStr(count);
    //pHeader->setCaption(newCaption);
    /*TODO 
    1) удалить всЄ из списка Container;
    2) пройтись по карте Alarms::Tags и добавить в контейнер все объекты
        у которых isValid = true, и State = false*/
}

void TPageAlarms::startToClose() {
  //count++;
  //std::string newCaption = Utils::UnSignedintToStr(count);
  //pHeader->setCaption(newCaption);
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

/*TODO если список, в высоту, не помещаетс€ на экране, то при при прокрутке вниз/ввеох
тер€етс€ фиксированный текст THeaderLabel(ј¬ј–»я)*/
void TPageAlarms::fillPageContainer(void) {
    TLabelInitStructure LabelInit;

    LabelInit.pOwner = Container;
    LabelInit.caption = "Header";
    TFixedHeader* pHeader = new TFixedHeader(LabelInit);
    Container->Add(pHeader);
    LabelInit.caption = "Footer";
    TFixedFooter* pFooter = new TFixedFooter(LabelInit);

    TVerticalContainer* pLabels = new TVerticalContainer({});
    pLabels->ElementRect = { 0, 0,// (s16)(pHeader->getHeight() - 2),
                                (u16)(VIEW_PORT_MAX_HEIGHT - pFooter->getHeight() - pHeader->getHeight() - 1),
                                VIEW_PORT_MAX_WIDTH };
    Container->Add(pLabels);
    
    LabelInit.Rect = {0, 0, 0, VIEW_PORT_MAX_WIDTH };

    LabelInit.style = LabelsStyle::WIDTH_DINAMIC;
    for (auto& e : Alarms::Tags) {
        if ((e.second.isValid) && (e.second.State == true)) {
            TBit* p = e.second.pBit;
            LabelInit.caption = p->getComment();
            TLinkLabel* pLabel = new TLinkLabel(LabelInit.caption, "Home", LabelInit);
            pLabels->Add(pLabel);
        }
    }
    pLabels->Add(new TLinkLabel("1 TLinkLabel TLinkLabel", "Home", LabelInit));
    pLabels->Add(new TLinkLabel("2 TLinkLabel TLinkLabel", "Home", LabelInit));
    pLabels->Add(new TLinkLabel("3 TLinkLabel TLinkLabel", "Home", LabelInit));
    
    pLabels->Add(new TLinkLabel("4 TLinkLabel", "Home", LabelInit));
    pLabels->Add(new TLinkLabel("5 TLinkLabel", "Home", LabelInit));
    
    pLabels->Add(new TLinkLabel("6", "Home", LabelInit));
    pLabels->Add(new TLinkLabel("7", "Home", LabelInit));
    pLabels->Add(new TLinkLabel("8", "Home", LabelInit));
 
    pLabels->Add(new TLinkLabel("9", "Home", LabelInit));
    pLabels->Add(new TLinkLabel("10", "Home", LabelInit));
    pLabels->Add(new TLinkLabel("11", "Home", LabelInit));
    pLabels->Add(new TLinkLabel("12", "Home", LabelInit));
    pLabels->Add(new TLinkLabel("13", "Home", LabelInit));
    pLabels->Add(new TLinkLabel("14", "Home", LabelInit));
    pLabels->Add(new TLinkLabel("15", "Home", LabelInit));
    pLabels->Add(new TLinkLabel("16", "Home", LabelInit));
    Container->Add(pFooter);
}

TPageAlarms::TPageAlarms(std::string Name)
    :TPage(Name) {
    Container = new TComponentListVertical({});
    AddList({ Container });
};

TPageAlarms::~TPageAlarms() {
};
