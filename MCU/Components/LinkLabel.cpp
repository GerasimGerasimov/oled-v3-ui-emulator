#include "LinkLabel.h"
#include "Router.h"


bool TLinkLabel::ProcessMessage(TMessage* m) {
    TScrollLabel::ProcessMessage(m);
    switch (m->Event) {
        case (u32)EventSrc::KEYBOARD: //сообщения от клавиатуры
            if (inFocus) {
                switch (m->p1) {
                    case (u32)KeyCodes::ENT: {
                        TRouter::setTask({ false, URL, NULL });
                        return true;
                    }
                }
            }
            break;
    }
    return false;
}

TLinkLabel::TLinkLabel(std::string caption, std::string url, TLabelInitStructure init)
    : TScrollLabel(caption, init)
    , URL(url)
    {}

TLinkLabel::~TLinkLabel() {//деструктор
}
