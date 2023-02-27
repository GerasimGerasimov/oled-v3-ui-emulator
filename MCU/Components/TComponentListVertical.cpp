#include "TComponentListVertical.h"

bool TComponentListVertical::ProcessMessage(TMessage* m){//���������� ���������
    if (ItemsCount() == 0) return false;//������ ����

    for (auto& element : List) {
        if (element->ProcessMessage(m)) {
            return false;
        };
    }

    switch (m->Event) {
        case (u32)EventSrc::KEYBOARD:{//��������� �� ����������
            switch (m->p1) {
                case (u32)KeyCodes::Up:{//������ �����
                    goUp();
                    return false;
                }
                case (u32)KeyCodes::Down:{//������ ����
                    goDown();
                    return false;
                }
            }
            return false;
        }
    }
    return false;
}

/*TODO ������� ����� � ���������� ��� ���� �� � ���� �����, �� ������ ��� ���������� � ��� ��������� (���� ���� �������)
� ���� �� ��������� ������... �� ������ ��������� � ����������*/

void TComponentListVertical::goUp(void) {
    if (ItemsCount() == 0) return;
    int fl = 0;
    u16 idx = 0;

    List[FocusedLine]->inFocus = false;//�������������� ���������� ������
    fl = FocusedLine;
    //��������� ������� (���� �� ������� ������������) ������ ����:
    fl--;
    if (fl < 0) fl = 0;
    u16 Count = ItemsCount();
    while (Count--)
    {
        if (fl == Count) {
            if (List[Count]->isSkipped) {
                if (fl-- <= 0) {//�� ��������� �� ������� ������� � ���������� ���� �� ��� ����
                    FocusedLine = (ItemsCount() > 1) ? 1 : 0;
                    List[FocusedLine]->inFocus = true;
                    break;
                }
            }
            else {
                FocusedLine = fl;
                List[Count]->inFocus = true;
                break;
            }
        }
    }

    //List[FocusLine]->inFocus = false;//�������������� ���������� ������
    //if (FocusLine > 0) FocusLine--;
    //List[FocusLine]->inFocus = true;//����������� ������
}

void TComponentListVertical::goDown(void) {
    u16 Count = ItemsCount();
    if (Count == 0) return;

    u16 fl = 0;
    u16 idx = 0;


    List[FocusedLine]->inFocus = false;//�������������� ���������� ������
    //����� ���������� ������� (���� �� FocusLine)
    fl = FocusedLine;
    //��������� ������� (���� �� ������� ������������) ������ ����:
    fl++;
    if (fl == Count) fl = Count - 1;
    idx = 0;
    for (auto& e: List) {
        if (fl == idx) {
            if (e->isSkipped) {
                if (fl++ == Count) fl = Count - 1;
            }
            else {
                FocusedLine = fl;
                e->inFocus = true;
                break;
            }
        }
        idx++;
    }

    //List[FocusLine]->inFocus = false;//�������������� ���������� ������
    //if ((FocusLine < (Count - 1)) && (Count != 0)) FocusLine++;
    //List[FocusLine]->inFocus = true;//����������� ������
}

TVisualObject* TComponentListVertical::getFocusedElement() {
    if (List.size()) {
        TVisualObject* p = List.at(FocusedLine);
        return p;
    }
    
    return NULL;
};

void TComponentListVertical::view(void){//������� ������ �� ������
    if (ItemsCount() == 0) return;//�������� ������
    TGraphics::fillRect({ ElementRect.Left, ElementRect.Top , ElementRect.Width, ElementRect.Height, 0});
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
  if (FocusedLine <= FirstPosition)  FirstPosition = FocusedLine ;//���� ���� �������
  if ((FocusedLine >= LastPosition) && (FocusedLine < ItemsCount()))  FirstPosition++;//���� ���� ������, �� �� ������ ��� ���� � ������, �� ��������� �������
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
  FocusedLine = FirstPosition = 0;
  LastPosition = 1;
}

TComponentListVertical::TComponentListVertical (std::vector <TVisualObject*> Source) {//�����������
  isOpen = false;
  inFocus = false;
  FocusedLine = FirstPosition = 0;
  LastPosition = 1;
  ElementRect = { 0, 0, VIEW_PORT_MAX_HEIGHT, VIEW_PORT_MAX_WIDTH };
  AddList(Source);
}

TComponentListVertical::~TComponentListVertical() {
};
