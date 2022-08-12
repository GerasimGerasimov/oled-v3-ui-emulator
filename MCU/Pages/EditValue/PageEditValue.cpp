#include "PageEditValue.h"
#include "Router.h"


void TPageEditValue::view() {
    Container->view();
};

void TPageEditValue::clear() {
}

bool TPageEditValue::ProcessMessage(TMessage* m) {
    switch (m->Event) {
        case KEYBOARD: {
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
    LabelInit.style = LabelsStyle::WIDTH_DINAMIC;
    LabelInit.Rect = { 10, 10, 10, 10 };
    LabelInit.caption = "1 Привет Edit";
    LabelInit.focused = false;
    pLabel1 = new TLabel(LabelInit);
    LabelInit.caption = "2 Привет Edit";
    pLabel2 = new TLabel(LabelInit);
    LabelInit.caption = "Values";
    pLabel3 = new TLinkLabel("Values", LabelInit);
    Container = new TComponentListVertical({ pLabel1, pLabel2, pLabel3});
    AddList({ Container });
};

TPageEditValue::~TPageEditValue() {
};
