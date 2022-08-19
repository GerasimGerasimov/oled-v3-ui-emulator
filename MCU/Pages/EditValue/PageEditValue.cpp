#include "PageEditValue.h"
#include "Router.h"
#include "parameters.h"

void TPageEditValue::view() {
    MainMenu->view();
};

void TPageEditValue::clear() {
}

void TPageEditValue::onOpen() {
    TParameter* p = (TParameter*)TRouter::PageValueEditEntryData.signal;
    pHeader->setCaption(p->getName());
    //pText->setText(p->getComment());
    pEdit->setCaption(TRouter::PageValueEditEntryData.value);
}

bool TPageEditValue::ProcessMessage(TMessage* m) {
    switch (m->Event) {
        case (u32)EventSrc::KEYBOARD: {
            switch (m->p1) {
            case (u32)KeyCodes::ESC:
                TRouter::goBack();
                break;
            }
        }
    }

    for (auto& element : List) {
        element->ProcessMessage(m);
    }
    return false;
};

TPageEditValue::TPageEditValue(std::string Name)
/*TODO � ���� ����
1) ������ �������������� ������� �� ���� ���������:
1.1) TBit ����� ��������� ������� ������ "0"/"1"
1.2) TIPAddr ����� ����� ������������ ����� ������� � ������ ������ �� ��
1.3) TPrmList - ���������� ����� �� ������ ��������

1) ������ ���� ��������� � ��������� ��������� (����)
2) ���� � ��������� (� ����� ����)
3) ������� �������� (TODO � ������ �������, ������� ���-�� ���� ��������) + ������� ��������� (���� ����)
4) ����� �������� ������� �������������� ���� (���������� ����� ������� �������)
�������� ��������������:
5) ������: ���� ��� ���������: ��� "1", �������:
    - ����������� � 10 ��� ��� ������ ������� "�����"
    - ������������� � 10 ��� ��� ������ ������� "������"
    - �������� ������������� �� ��� ��������� ��� ������� "�����"
    - �������� ����������� �� ��� ��������� ��� ������� "����"
    TODO ������������� �������������� ��������� �������� �� �������, ��� ���������� ��������� ������ "�����/����"
6) �����:
    - ������������� "�����/������" ����������� � ������ ����� ������� ���� ����������, ���� ������� ���, �� �� ��������
      ___.____ ������� ������� � �������� ���� ��������� ��� ������ � ��� ������ ������
        - � ������� �������� ������� ��� ����� ����� �����
        - � ������� �������� ������� ��� ������� ����� �����
    ���� ���������� � ������ ������ ��� ����������� �������, �����-�� ���� ���� �� ��������
    �������� �������� �� ��� ���� ���������
*/
    :TPage(Name) {
    TLabelInitStructure LabelInit;
    LabelInit.style = (LabelsStyle)((u32)LabelsStyle::WIDTH_FIXED | (u32)LabelsStyle::TEXT_ALIGN_CENTER);
    LabelInit.Rect = { 10, 10, 10, VIEW_PORT_MAX_WIDTH };
    LabelInit.focused = true;

    LabelInit.caption = "---";
    pHeader = new THeaderLabel(LabelInit);

    //pText = new TWrappedText(LabelInit);

    pEdit = new TNumericEdit(LabelInit);

    MainMenu = new TComponentListVertical({ pHeader, pEdit });

    //pText->ElementRect.Height = MainMenu->ElementRect.Height - pHeader->getHeight() - pEdit->getHeight();

    AddList({ MainMenu });
};

TPageEditValue::~TPageEditValue() {
};
