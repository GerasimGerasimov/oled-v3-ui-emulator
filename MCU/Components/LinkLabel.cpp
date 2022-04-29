#include "LinkLabel.h"
#include "Router.h"

bool TLinkLabel::onEnter(void) {
    return (TRouter::setActivePage(URL) == NULL) ? false : true;
}

TLinkLabel::TLinkLabel(std::string url, TLabelInitStructure init)
    :TLabel(init) {
    URL = url;
}

TLinkLabel::~TLinkLabel() {//деструктор
}
