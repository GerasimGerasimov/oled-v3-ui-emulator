#include "LinkLabel.h"
#include "Router.h"

bool TLinkLabel::ProcessMessage(TMessage* m) {
    switch (m->Event) {
        case KEYBOARD: {//сообщения от клавиатуры
            if (inFocus) {
                switch (m->p1) {
                case kbENT: {
                    onEnter();
                    break;
                }
                }
            }
        }
    }
    return true;
}

bool TLinkLabel::onEnter(void) {
    return (TRouter::setActivePage(URL) == NULL) ? false : true;
}

TLinkLabel::TLinkLabel(std::string url, TLabelInitStructure init)
    :TLabel(init) {
    URL = url;
}

TLinkLabel::~TLinkLabel() {//деструктор
}
