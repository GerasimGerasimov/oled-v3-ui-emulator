#include "PageAlarms.h"
#include "Router.h"
#include <utils.h>
#include <HeaderLabel.h>
#include "Alarms.h"
#include "LinkLabel.h"

static u16 count;

void TPageAlarms::onOpen() {
    Container->Clear();
    fillPageContainer();
    //count++;
    //std::string newCaption = Utils::UnSignedintToStr(count);
    //pHeader->setCaption(newCaption);
    /*TODO 
    1) удалить всё из списка Container;
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

/*TODO если список, в высоту, не помещается на экране, то при при прокрутке вниз/ввеох
теряется фиксированный текст THeaderLabel(АВАРИЯ)*/
void TPageAlarms::fillPageContainer(void) {
    TLabelInitStructure LabelInit;

    LabelInit.style = (LabelsStyle)((u32)LabelsStyle::WIDTH_FIXED | (u32)LabelsStyle::TEXT_ALIGN_CENTER);
    LabelInit.Rect = { 10, 10, 10, VIEW_PORT_MAX_WIDTH };

    LabelInit.caption = "Аварии";
    THeaderLabel* pHeader = new THeaderLabel(LabelInit);
    Container->Add(pHeader);
    LabelInit.style = LabelsStyle::WIDTH_DINAMIC;
    for (auto& e : Alarms::Tags) {
        if ((e.second.isValid) && (e.second.State == true)) {
            TBit* p = e.second.pBit;
            LabelInit.caption = p->getComment();
            TLinkLabel* pLabel = new TLinkLabel(LabelInit.caption, "Home", LabelInit);
            Container->Add(pLabel);
        }
        Container->Add(new TLinkLabel("Основные параметры", "Home", LabelInit));
        Container->Add(new TLinkLabel("Предупреждения", "Home", LabelInit));
        Container->Add(new TLinkLabel("Аварии", "Alarms", LabelInit));
        Container->Add(new TLinkLabel("Основные уставки работы", "Home", LabelInit));
        Container->Add(new TLinkLabel("Уставки защит", "Home", LabelInit));
    }
}

TPageAlarms::TPageAlarms(std::string Name)
    :TPage(Name) {
    Container = new TComponentListVertical({});
    AddList({ Container });
};

TPageAlarms::~TPageAlarms() {
};
