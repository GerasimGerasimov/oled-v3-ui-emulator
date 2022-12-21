#include "LinkedTagLabel.h"
#include "IniResources.h"

bool TLinkedTagLabel::ProcessMessage(TMessage* m) {
    switch (m->Event) {
        case (u32)EventSrc::KEYBOARD: {//��������� �� ����������
            if (inFocus) {
                switch (m->p1) {
                    case (u32)KeyCodes::ENT: {
                        break;
                    }
                }
            }
        }
    }
    return false;
}

TLinkedTagLabel::TLinkedTagLabel(std::string tag, TLabelInitStructure init)
    : TLinkLabel(init.caption, "", init)
    , DataSrc(IniResources::getSignalByTag(tag)) {
}

TLinkedTagLabel::~TLinkedTagLabel() {//����������
}

void TLinkedTagLabel::view(void) {
    TLinkLabel::view();//������� Coption
    /*TODO ���� ������� �������� ����*/
    /*TODO ���� ������� ��.��� ����*/
}
