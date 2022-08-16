#include "PageEditValue.h"
#include "Router.h"
#include "parameters.h"

void TPageEditValue::view() {
    MainMenu->view();
};

void TPageEditValue::clear() {
}

void TPageEditValue::onOpen() {
    TParameter* p = (TParameter*)props;
    pHeader->setCaption(p->getName());
    pText->setText(p->getComment());
}

bool TPageEditValue::ProcessMessage(TMessage* m) {
    switch (m->Event) {
        case (u32)EventSrc::KEYBOARD: {
            switch (m->p1) {
            case (u32)KeyCodes::ESC:
                TRouter::goBack();
                break;
            }
        }
    }

    for (auto& element : List) {
        element->ProcessMessage(m);
    }
    return false;
};

TPageEditValue::TPageEditValue(std::string Name)
    :TPage(Name) {
    TLabelInitStructure LabelInit;
    LabelInit.style = (LabelsStyle)((u32)LabelsStyle::WIDTH_FIXED | (u32)LabelsStyle::TEXT_ALIGN_CENTER);
    LabelInit.Rect = { 10, 10, 10, VIEW_PORT_MAX_WIDTH };
    LabelInit.focused = true;

    LabelInit.caption = "---";
    pHeader = new THeaderLabel(LabelInit);

    pText = new TWrappedText(LabelInit);

    MainMenu = new TComponentListVertical({ pHeader, pText });

    pText->ElementRect.Height = MainMenu->ElementRect.Height - pHeader->getHeight();

    AddList({ MainMenu });
};

TPageEditValue::~TPageEditValue() {
};
