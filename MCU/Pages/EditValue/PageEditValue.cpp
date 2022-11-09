#include "PageEditValue.h"
#include "Router.h"
#include <IniResources.h>

void TPageEditValue::view() {
    MainMenu->view();
};

void TPageEditValue::clear() {
}

void TPageEditValue::onOpen() {
    p = (TParameter*)IniResources::getSignalByTag(TRouter::PageValueEditEntryData.tag);
    pHeader->setCaption(p->getName());
    pEdit->setCaption(TRouter::PageValueEditEntryData.value);
    tag = TRouter::PageValueEditEntryData.tag;
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

std::string NetWorkAddrToHex(u16 nwa) {
    char s[4];
    sprintf(s, "%.2X", nwa);
    std::string res(s);
    return res;
}

typedef struct {
    const std::string& Cmd;
    const std::string& DevAddr;
    const std::string& RegAddr;
    const std::string& Value;
} TWriteCmdSrc;

std::string get0x10WriteRegCmd(TWriteCmdSrc& CmdSrc) {
    return "Write Multiple Registers";
}

static const std::map<std::string, std::function<std::string(TWriteCmdSrc&)>> WriteCmdVariants = {
    {"10", [](TWriteCmdSrc& props) {return "Write Multiple Registers"; }},
    {"16", [](TWriteCmdSrc& props) {return " Mask Write Register"; }},
};

std::string CreateWriteCmd(TWriteCmdSrc CmdSrc) {
    std::string res = (WriteCmdVariants.count(CmdSrc.Cmd))
        ? WriteCmdVariants.at(CmdSrc.Cmd)(CmdSrc)
        : "Unknown Reg Write Command";
    return res;
}

void TPageEditValue::sendValue(void) {
    u8 cmd[11];
    std::string value = pEdit->getValue();
    std::string ValueHex = p->getValueHex(value);//������� �������� � ������ � ����� ����� (��� ��� ������)
    std::string RegHexAddr = p->getRegHexAddr();//������� ����� �������� � ������
    /*getWriteCmdType ����� ����� �������� ���������� ������
        Write Multiple Registers - 0�10
        Mask Write Register - 0x16 ��� ����������� � ������ � �������*/
    const std::string Cmd = p->getWriteCmdType();
    /*�� Tag ���� ����� �� ����� ����� ����������
    "DEVICES":"U1/", ���� ������ ���������, ���� ������������ �� ���� U1
        "U1":"DEV1/COM1/1 � �� U1 ����� ����� (�� �� COM1/)
    */
    const u16 DevAddr = IniResources::getDevNetWorkAddrByTag(tag);
    const std::string DevAddrHex = NetWorkAddrToHex(DevAddr);
    /*TODO �� ��������� �������, ������, ��������������, ������ - ������� ������ �������*/
    /*TODO � ���������� ������� �������� CRC16*/
    CreateWriteCmd({ Cmd, DevAddrHex, RegHexAddr, ValueHex });
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
