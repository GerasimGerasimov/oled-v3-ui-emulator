#include "WrappedText.h"
#include "parser.h"

/*TODO ��������� ��������� ��� �������������� ������ �� ������������� �� ����� ������*/
bool TWrappedText::ProcessMessage(TMessage* m) {
    if (List.size() == 0) return false;//������ ����
        switch (m->Event) {
            case (u32)EventSrc::KEYBOARD: {//��������� �� ����������
                switch (m->p1) {
                    case (u32)KeyCodes::Up: //������ �����
                        goUp();
                        break;
                    case (u32)KeyCodes::Down: //������ ����
                        goDown();
                        break;
                }
                break;
        }
    }
    return false;
}

void  TWrappedText::view(void) {//������� ������ �� ������
    if (List.size() == 0) return;//�������� ������
    TGraphics::fillRect({ ElementRect.Left, ElementRect.Top , ElementRect.Width, ElementRect.Height, 0 });
    //����������, ������� ��������(�����) ��������� � ������ TMenu ������� � FirstPosition
    //��� ����, FocusLine ������ � ��������� ����� FirstPosition � LastPosition
    u16 c = GetViewObjectsCount();//���-�� �������� ����������� � ������ ���� �� FirstPosition �� ������� ����
                                //��� � ���� ���-�� �������� ��������� �� ����� (�� �� ������ ��� ����� �� �����������)
    u16 i = FirstPosition;//���-�� �������� ��������� �� �����
    //u16 h = ElementRect.Top;//������� ���������� Y ������ ������
    u16 Left = ElementRect.Left;
    u16 Top = ElementRect.Top;
    u16 hf = TMCUFonts::getFontHeight(Font);
    //������ ��������� ������, � �������� ��������� ��������� ����� ��������� ���������� TMenu
    while (i != LastPosition) {//��������� �������� ���� � ������ ���-�� ���� 
        TGraphics::outText(List[i], Left, Top, 1, Font);
        Top += hf;
        i++;                    //�������� � ��������� ������
    }
}

void TWrappedText::goUp(void) {
    if (FirstPosition > 0) FirstPosition --;
}

void TWrappedText::goDown(void) {
    u16 Count = List.size();
    if ((FirstPosition < (Count - 1)) && (Count != 0)) FirstPosition++;
}

void TWrappedText::outText() {
    s16 Left = ElementRect.Left;
    s16 Top = ElementRect.Top;
    for (auto const text : List) {
        TGraphics::outText(text, Left, Top, 1, Font);
        Top+= TMCUFonts::getFontHeight(Font);
    }
}

const u16 TWrappedText::getHeight(void) {
    TTextSizes tsizes = getSize();
    return tsizes.height;
}


/*���� �������� ������, � ������� � �.�. ����� ���� � ������ �������� ������.
���� ������� �� ������ �������� � ������ ������. ������ ������ �������� �������� ����� ������.
������ � �������� ������ �� ����� ���������� ���������, ����� ����������� ������
���� ����� �������, �� ��� ���� ���� ��������� �� �����, �� �������� ������� ��������*/

void TWrappedText::setText(std::string text) {//��������/�������� ����� � ������
    //������ ������������ �� ������������ ����������� � ������ ����� ��������
    std::vector<std::string> res = {};
    u16 maxwidth = ElementRect.Width;
    std::string s = "";
    for (const char c: text) {
        if (c == '\n') {
            res.push_back(s);
            res.push_back("");
            s = "";
            continue;
        }
        TTextSizes ts = TMCUFonts::getTextSizes(s+c, Font);
        if (ts.width > maxwidth) {
            res.push_back(s);
            s = "";
        }
        s += c;
    }
    if (s != "") {
        res.push_back(s);
    }
    List.clear();
    List = res;
    //FocusLine = 0;
    FirstPosition = 0; //������ ������������ ������ ������� �������� � ��
    LastPosition = 0; //��������� ������������ ������
}

TTextSizes TWrappedText::getSize(void) {
    //u16 h = List.size() * TMCUFonts::getFontHeight(Font);
    return { ElementRect.Width, TMCUFonts::getFontHeight(Font) };
}

u16 TWrappedText::GetViewObjectsCount() {//���-�� ����� ����������� � ������ ���� �� FirstPosition �� ������� ����
    u16 i = FirstPosition;
    u16 c = 0;//������� �����
    u16 h = 0; //������ �������
    u16 sh = TMCUFonts::getFontHeight(Font);//������ ������
    while (h <= ElementRect.Height) {//
        if (i < List.size()) {
            h += sh;//���������� ������
            i++; //���������� ��������� �� ������
            c++; //���������� ���-�� ����� ����������� � ������� ����� ������
        }
        else {//��������� ������
            LastPosition = FirstPosition + c;//������� ����� ��������� ������������ ������
            return c;
        }
    }
    //������ ��������� ����������
    if (c > 0) c--;//�������� �����
    LastPosition = FirstPosition + c;//������� ����� ��������� ������������ ������
    return c;
}

TWrappedText::TWrappedText(TLabelInitStructure init)
    : TVisualObject({init.focused, init.Rect })
    , Font((init.font != "") ? init.font : "Verdana12")
    , FirstPosition(0)//������ ������������ ������ ������� �������� � ��
    , LastPosition(0) //��������� ������������ ������
    , List({}){
}

TWrappedText::~TWrappedText() {//����������
}
