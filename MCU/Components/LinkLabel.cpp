#include "LinkLabel.h"
#include "Router.h"

/*TODO ������� ��������� ��������� ����� (� ����� ������� � ������) 
���� ������� ��������� � ������, � ��� Caption �� ������ �� �����*/

bool TLinkLabel::ProcessMessage(TMessage* m) {
    switch (m->Event) {
        case (u32)EventSrc::KEYBOARD: //��������� �� ����������
            if (inFocus) {
                switch (m->p1) {
                    case (u32)KeyCodes::ENT: {
                        TRouter::setTask({ false, URL, NULL });
                        break;
                    }
                }
            }
            break;
        case (u32)EventSrc::TIMER:
            doShift();
            break;
    }
    return true;
}

void TLinkLabel::doShift(void) {
    if (inFocus) {
        /*��� ��������� � ������, ��������� ����� �������� ������� �� ��������� �� �����.
        ��� ������ ������ �����, ��������� � ����������� � ������ �����.
        ���� � ������, � ������ ���������� �������, �� �����,
        ����� ����� ������� ����� ������ �� ������ �����, �����,
        ��������� ����� �����.*/
        TLinkLabelVars.shifted = SrcCaption.substr(Shift);
        TextSize = TMCUFonts::getTextSizes(Caption, Font);
        if (TextSize.width > ElementRect.Width) {
            Shift++;
            Caption = TLinkLabelVars.shifted;
            TLinkLabelVars.ReturnPause = RETURN_PAUSE;
        }
        else {
            if (TLinkLabelVars.ReturnPause) {
                TLinkLabelVars.ReturnPause--;
                return;
            }
            if (Shift != 0) {
                Shift = 0;
                Caption = SrcCaption;
            }
        }
    }
    else {
        if (Caption != SrcCaption) {
            setCaption(SrcCaption);
            Shift = 0;
            TLinkLabelVars.ReturnPause = RETURN_PAUSE;
        }
    }
}

TLinkLabel::TLinkLabel(std::string caption, std::string url, TLabelInitStructure init)
    : TLabel(init)
    , URL(url)
    , SrcCaption(caption)
    , Shift(0) {
    Caption = caption;
}

TLinkLabel::~TLinkLabel() {//����������
}
