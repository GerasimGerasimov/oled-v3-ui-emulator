#include "PageCounters.h"
#include "Router.h"

static u32 COUNT = 0;

void TPageCounters::view() {
    Container->view();
};

void TPageCounters::clear() {
}

bool TPageCounters::ProcessMessage(TMessage* m) {
    switch (m->Event) {
        case KEYBOARD: {
            switch (m->p1) {
            case kbESC:
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

void TPageCounters::goToValueEditPage(int a) {
    //return (TRouter::setActivePage(URL) == NULL) ? false : true;
    TRouter::setActivePage("EditValue");
}

TPageCounters::TPageCounters(std::string Name)
    :TPage(Name) {
    TLabelInitStructure LabelInit;
    LabelInit.style = LabelsStyle::LS_DINAMIC;
    LabelInit.Rect = { 10, 10, 10, 10 };
    LabelInit.caption = "1 ������";
    LabelInit.focused = false;
    pLabel1 = new TLabel(LabelInit);
    LabelInit.caption = "2 ������";
    pLabel2 = new TLabel(LabelInit);
    LabelInit.caption = "EditValue";
    pLabel3 = new TLinkLabel("EditValue", LabelInit);
    pLabel3->onEnterPressed = [this](int arg) { goToValueEditPage(arg); };
    Container = new TComponentListVertical({ pLabel1, pLabel2, pLabel3});
    AddList({ Container });
};

TPageCounters::~TPageCounters() {
};