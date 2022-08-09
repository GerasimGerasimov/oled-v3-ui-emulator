#include "LinkLabel.h"

bool TLinkLabel::ProcessMessage(TMessage* m) {
    switch (m->Event) {
        case KEYBOARD: {//сообщения от клавиатуры
            if (inFocus) {
                switch (m->p1) {
                    case (u32)KeyCodes::ENT: {
                        if (onEnterPressed != NULL) {
                            onEnterPressed(10);
                        }
                        break;
                    }
                }
            }
        }
    }
    return true;
}

TLinkLabel::TLinkLabel(std::string url, TLabelInitStructure init)
    : TLabel(init)
    , URL(url)
    , onEnterPressed({}) {
}

TLinkLabel::~TLinkLabel() {//деструктор
}
