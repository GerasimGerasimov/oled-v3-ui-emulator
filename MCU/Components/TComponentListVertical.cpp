#include "TComponentListVertical.h"

void TComponentListVertical::ProcessMessage(TMessage* m){//���������� ���������
  u16 Count = ItemsCount();
  if ( Count == 0) return;//�������� ������
    switch (m->Event) {
        case KEYBOARD:{//��������� �� ����������
            switch (m->p1) {
                case kbUp:{//������ �����
                    List[FocusLine]->inFocus = false;//�������������� ���������� ������
                    if (FocusLine > 0) FocusLine--;
                    List[FocusLine]->inFocus = true;//����������� ������
                    break;
                }
                case kbDown:{//������ ����
                    List[FocusLine]->inFocus = false;//�������������� ���������� ������
                    if ((FocusLine < (Count -1)) && (Count !=0)) FocusLine++;
                    List[FocusLine]->inFocus = true;//����������� ������
                    break;
                }
                case kbENT: {
                    TVisualObject* p = List[FocusLine];
                    break;
                }

            }
            break;
        }
    }
}

void TComponentListVertical::view(void){//������� ������ �� ������
    if (ItemsCount() == 0) return;//�������� ������
    //FillRect(Left, Top, Width, Height, 0);
    //����������, ������� ��������(�����) ��������� � ������ TMenu ������� � FirstPosition
    //��� ����, FocusLine ������ � ��������� ����� FirstPosition � LastPosition
    u16 c = GetViewObjectsCount();//���-�� �������� ����������� � ������ ���� �� FirstPosition �� ������� ����
                                //��� � ���� ���-�� �������� ��������� �� ����� (�� �� ������ ��� ����� �� �����������)
    u16 i = FirstPosition;//���-�� �������� ��������� �� �����
    u16 h = ElementRect.Top;//������� ���������� Y ������ ������
    //������ ��������� ������, � �������� ��������� ��������� ����� ��������� ���������� TMenu
    while (i != LastPosition) {//��������� �������� ���� � ������ ���-�� ���� 
        //����� ������� ������, ��������� ������ � ����������,
        //�������� ���������� Top � ����������� �� ������ ����������� �������
        List[i]->ElementRect.Left  = ElementRect.Left;  //����� ���������� �
        List[i]->ElementRect.Width = ElementRect.Width; //������ ������ = ������ ����������
        List[i]->ElementRect.Top  = h;      //����� ���������� Y
        h += List[i]->getHeight();   //���������� ���������� Y ��� ��������� ������
        List[i]->view();        //������ ��������� ������
        i++;                    //�������� � ��������� ������
    }
}

u16 TComponentListVertical::getHeight(void) {
    return ElementRect.Height;
}

u16 TComponentListVertical::GetViewObjectsCount(){//���-�� �������� ����������� � ������ ���� �� FirstPosition �� ������� ����
//��� ���� ����������� �������
  if (FocusLine <= FirstPosition)  FirstPosition = FocusLine ;//���� ���� �������
  if ((FocusLine >= LastPosition) && (FocusLine < ItemsCount()))  FirstPosition++;//���� ���� ������, �� �� ������ ��� ���� � ������, �� ��������� �������
  u16 i = FirstPosition;
  u16 c = 0;//������� �����
  u16 h = 0; //������ �������
  while (h <= ElementRect.Height) {//
    if (i < ItemsCount()) {
      h += List[i]->ElementRect.Height;//���������� ������
      i++; //���������� ��������� �� ������
      c++; //���������� ���-�� ����� ����������� � ������� ����� ������
    }
    else {//��������� ������
      LastPosition = FirstPosition + c;//������� ����� ��������� ������������ ������
      return c;
    }
  }
  //������ ��������� ����������
  if (c>0) c--;//�������� �����
  LastPosition = FirstPosition + c;//������� ����� ��������� ������������ ������
  return c;
}

void TComponentListVertical::Add(TVisualObject* pVisualObject){//�������� ������ � ������
  List.push_back(pVisualObject);
}

void TComponentListVertical::AddList(std::vector <TVisualObject*> Source) {//�������� ������ �������� � ������
    List.assign(Source.begin(), Source.end());
}

void  TComponentListVertical::Clear(){//������� ������
  List.clear();
  FocusLine = LastPosition = FirstPosition = 0;
}

TComponentListVertical::TComponentListVertical (std::vector <TVisualObject*> Source) {//�����������
  isOpen = false;
  inFocus = false;
  FocusLine = FirstPosition = 0;
  LastPosition = 1;
  ElementRect = { 0, 0, VIEW_PORT_MAX_WIDTH, VIEW_PORT_MAX_HEIGHT };
  AddList(Source);
}

const u16 TComponentListVertical::ItemsCount() const {
    return List.size();
}

TComponentListVertical::~TComponentListVertical() {
};
