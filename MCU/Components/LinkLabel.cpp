#include "LinkLabel.h"

bool TLinkLabel::ProcessMessage(TMessage* m) {
    switch (m->Event) {
        case KEYBOARD: {//��������� �� ����������
            if (inFocus) {
                switch (m->p1) {
                    case kbENT: {
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

TLinkLabel::~TLinkLabel() {//����������
}