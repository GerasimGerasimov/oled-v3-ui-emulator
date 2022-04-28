#include "LinkLabel.h"


TLinkLabel::TLinkLabel(std::string url, TLabelInitStructure init)
    :TLabel(init) {
    URL = url;
}

TLinkLabel::~TLinkLabel() {//деструктор
}
