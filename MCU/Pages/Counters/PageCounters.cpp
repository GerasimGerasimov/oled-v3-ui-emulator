#include "PageCounters.h"

static u32 COUNT = 0;

void TPageCounters::view() {
    Container->view();
};

void TPageCounters::clear() {
}

void TPageCounters::ProcessMessage(TMessage* m) {
    for (auto& element : List) {
        element->ProcessMessage(m);
    }
};

TPageCounters::TPageCounters(std::string Name)
    :TPage(Name) {
    TLabelInitStructure LabelInit;
    LabelInit.style = LabelsStyle::LS_DINAMIC;
    LabelInit.Rect = { 10, 10, 10, 10 };
    LabelInit.caption = "1 ������";
    LabelInit.focused = true;
    pLabel1 = new TLabel(LabelInit);

    Container = new TComponentListVertical({ pLabel1});
    AddList({ Container });
};

TPageCounters::~TPageCounters() {
};
