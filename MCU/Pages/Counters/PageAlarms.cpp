#include "PageAlarms.h"
#include "Router.h"
#include <utils.h>

static u16 count;

void TPageAlarms::onOpen() {
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

TPageAlarms::TPageAlarms(std::string Name)
    :TPage(Name) {
    TLabelInitStructure LabelInit;

    LabelInit.style = (LabelsStyle)((u32)LabelsStyle::WIDTH_FIXED | (u32)LabelsStyle::TEXT_ALIGN_CENTER);
    LabelInit.Rect = { 10, 10, 10, VIEW_PORT_MAX_WIDTH };
    LabelInit.focused = false;

    LabelInit.caption = "Аварии";
    pHeader = new THeaderLabel(LabelInit);
    Container = new TComponentListVertical({ pHeader});
    AddList({ Container });
};

TPageAlarms::~TPageAlarms() {
};
