#include "LinkedTagLabel.h"

bool TLinkedTagLabel::ProcessMessage(TMessage* m) {
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

TLinkedTagLabel::TLinkedTagLabel(std::string url, std::string tag, TLabelInitStructure init)
    : TLinkLabel(url,init)
    , Tag(tag) {
}

TLinkedTagLabel::~TLinkedTagLabel() {//����������
}
