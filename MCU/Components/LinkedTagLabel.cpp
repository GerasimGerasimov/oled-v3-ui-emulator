#include "LinkedTagLabel.h"
#include "IniResources.h"

bool TLinkedTagLabel::ProcessMessage(TMessage* m) {
    switch (m->Event) {
        case KEYBOARD: {//сообщения от клавиатуры
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

TLinkedTagLabel::TLinkedTagLabel(std::string tag, TLabelInitStructure init)
    : TLinkLabel("", init)
    , DataSrc(IniResources::getSignalByTag(tag)) {
}

TLinkedTagLabel::~TLinkedTagLabel() {//деструктор
}

void TLinkedTagLabel::view(void) {
    TLinkLabel::view();//выводит Coption
    /*TODO надо вывести значение тега*/
    /*TODO надо вывести ед.изм тега*/
}
