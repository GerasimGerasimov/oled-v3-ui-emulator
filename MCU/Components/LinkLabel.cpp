#include "LinkLabel.h"
#include "Router.h"

/*TODO ������� ��������� ��������� ����� (� ����� ������� � ������) 
���� ������� ��������� � ������, � ��� Caption �� ������ �� �����*/

bool TLinkLabel::ProcessMessage(TMessage* m) {
    switch (m->Event) {
        case KEYBOARD: {//��������� �� ����������
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

TLinkLabel::~TLinkLabel() {//����������
}
