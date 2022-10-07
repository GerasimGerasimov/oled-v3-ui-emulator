#include "PageEditValue.h"
#include "Router.h"

void TPageEditValue::view() {
    MainMenu->view();
};

void TPageEditValue::clear() {
}

void TPageEditValue::onOpen() {
    p = (TParameter*)TRouter::PageValueEditEntryData.signal;
    pHeader->setCaption(p->getName());
    pEdit->setCaption(TRouter::PageValueEditEntryData.value);
}

bool TPageEditValue::ProcessMessage(TMessage* m) {
    for (auto& element : List) {
       element->ProcessMessage(m);
    }

    switch (m->Event) {
        case (u32)EventSrc::KEYBOARD: {
            switch (m->p1) {
                case (u32)KeyCodes::ESC:
                    TRouter::goBack();
                    return true;
                case (u32)KeyCodes::ENT:
                    sendValue();
                    TRouter::goBack();
                    return true;
                }
        }
    }
    return false;
};

void TPageEditValue::sendValue(void) {
    u8 cmd[11];
    std::string value = pEdit->getValue();
    std::string ValueHex = p->getValueHex(value);//������� �������� � ������ � ����� ����� (��� ��� ������)
    std::string RegHexAddr = p->getRegHexAddr();//������� ����� �������� � ������
    /*getWriteCmdType ����� ����� �������� ���������� ������
        Write Multiple Registers - 0�10
        Mask Write Register - 0x16 ��� ����������� � ������ � �������*/
    const std::string WriteCmdType = p->getWriteCmdType();
    /*TODO ������ ���� ������ �� ����� ����� ����������*/
    /*TODO �� ��������� ������, �������, ��������������, ������ - ������� ������ �������*/
    /*TODO � ���������� ������� �������� CRC16*/
    /*TODO ������� � ����� ��������� ���� ������*/
    /*TODO ���������� ������ �������� � OUT ���������� �����*/
    /*TODO ������������ ���� �� �������� � ���������� �������� �� ���������� ������*/
    /*TODO ���� ������ ������� - �������� ������� �������� �������, ���� ��� ����� ����������*/
}

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
    :TPage(Name)
    , p(NULL) {
    TLabelInitStructure LabelInit;
    LabelInit.style = (LabelsStyle)((u32)LabelsStyle::WIDTH_FIXED | (u32)LabelsStyle::TEXT_ALIGN_CENTER);
    LabelInit.Rect = { 10, 10, 10, VIEW_PORT_MAX_WIDTH };
    LabelInit.focused = false;

    LabelInit.caption = "---";
    pHeader = new THeaderLabel(LabelInit);

    LabelInit.focused = true;
    pEdit = new TNumericEdit(LabelInit);

    MainMenu = new TComponentListVertical({ pHeader, pEdit });

    AddList({ MainMenu });
};

TPageEditValue::~TPageEditValue() {
};
