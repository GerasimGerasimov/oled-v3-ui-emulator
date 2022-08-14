#include "LinkLabel.h"
#include "Router.h"

/*TODO сделать медленную прокрутку влево (а затем переход в начало) 
если элемент находится в фокусе, а его Caption не входит на экран*/

bool TLinkLabel::ProcessMessage(TMessage* m) {
    switch (m->Event) {
        case KEYBOARD: {//сообщения от клавиатуры
            if (inFocus) {
                switch (m->p1) {
                    case (u32)KeyCodes::ENT: {
                        TRouter::setTask({ false, URL, NULL });
                        break;
                    }
                }
            }
        }
    }
    return true;
}

TLinkLabel::TLinkLabel(std::string caption, std::string url, TLabelInitStructure init)
    : TLabel(init)
    , URL(url) {
    Caption = caption;
}

TLinkLabel::~TLinkLabel() {//деструктор
}
