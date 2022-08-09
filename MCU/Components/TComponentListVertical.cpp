#include "TComponentListVertical.h"

bool TComponentListVertical::onEnter(void) {
    return true;
}

bool TComponentListVertical::ProcessMessage(TMessage* m){//���������� ���������
  if (ItemsCount() == 0) return false;//������ ����
    switch (m->Event) {
        case KEYBOARD:{//��������� �� ����������
            switch (m->p1) {
                case (u32)KeyCodes::Up:{//������ �����
                    goUp();
                    break;
                }
                case (u32)KeyCodes::Down:{//������ ����
                    goDown();
                    break;
                }
            }
            break;
        }
    }
    for (auto& element : List) {
        element->ProcessMessage(m);
    }
    return false;
}

void TComponentListVertical::goUp(void) {
    List[FocusLine]->inFocus = false;//�������������� ���������� ������
    if (FocusLine > 0) FocusLine--;
    List[FocusLine]->inFocus = true;//����������� ������
}

void TComponentListVertical::goDown(void) {
    u16 Count = ItemsCount();
    List[FocusLine]->inFocus = false;//�������������� ���������� ������
    if ((FocusLine < (Count - 1)) && (Count != 0)) FocusLine++;
    List[FocusLine]->inFocus = true;//����������� ������
}

std::vector<TVisualObject*> TComponentListVertical::getFocusedElements() {
    std::vector<TVisualObject*> res = {};
    TVisualObject* p = List[FocusLine];
    if (p->inFocus) res.push_back(p);
    return res;
};

void TComponentListVertical::view(void){//������� ������ �� ������
    if (ItemsCount() == 0) return;//�������� ������
    TGrahics::fillRect({ ElementRect.Left, ElementRect.Top , ElementRect.Width, ElementRect.Height, 0});
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

const u16 TComponentListVertical::getHeight(void) {
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
      h += List[i]->getHeight();//���������� ������
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

void  TComponentListVertical::Clear(){//������� ������
  TComponentsContainer::Clear();
  FocusLine = LastPosition = FirstPosition = 0;
}

TComponentListVertical::TComponentListVertical (std::vector <TVisualObject*> Source) {//�����������
  isOpen = false;
  inFocus = false;
  FocusLine = FirstPosition = 0;
  LastPosition = 1;
  ElementRect = { 0, 0, VIEW_PORT_MAX_HEIGHT, VIEW_PORT_MAX_WIDTH };
  AddList(Source);
}

TComponentListVertical::~TComponentListVertical() {
};
