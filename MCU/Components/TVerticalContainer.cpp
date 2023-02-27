#include "TVerticalContainer.h"

/*TODO � � TVerticalContainer ������ ��������� � TComponentListVertical �� WrappedText
������������ �������� DRY*/

static const u8 ScrollBarWidth = 2;
static const u8 MarginBottom = 1;
bool TVerticalContainer::onEnter(void) {
    return true;
}

bool TVerticalContainer::ProcessMessage(TMessage* m){//���������� ���������
    if (ItemsCount() == 0) return false;//������ ����

    for (auto& element : List) {
        if (element->ProcessMessage(m)) {
            return false;
        };
        //����� ���������, ��� ���� �������� ������ TRUE, ������ ���� ��������
        //������ ��������� 
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

void TVerticalContainer::goUp(void) {
    if (ItemsCount() == 0) return;
    int fl = 0;

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
}

void TVerticalContainer::goDown(void) {
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
}

TVisualObject* TVerticalContainer::getFocusedElement() {
    if (List.size()) {
        TVisualObject* p = List.at(FocusedLine);
        return p;
    }
    return nullptr;
};

void TVerticalContainer::view(void){//������� ������ �� ������
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
        List[i]->ElementRect.Width = ElementRect.Width - getScrollBarWidth(); //������ ������ = ������ ����������
        List[i]->ElementRect.Top  = h + MarginBottom;      //����� ���������� Y
        List[i]->ElementRect.Height = List[i]->getHeight();
        h += List[i]->ElementRect.Height;   //���������� ���������� Y ��� ��������� ������
        List[i]->view();        //������ ��������� ������
        i++;                    //�������� � ��������� ������
    }
    drawScrollBar();
}

inline u16 TVerticalContainer::getScrollBarWidth() {
    return (EnableScrollBar) ? ScrollBarWidth : 0;
}

void TVerticalContainer::drawScrollBar(void) {
    if (!EnableScrollBar) return;
    s16 items = ItemsCount();
    u16 ScrlBarHeight = (items) ? ElementRect.Height / items : ElementRect.Height;
    ScrlBarHeight = (ScrlBarHeight < ScrollBarWidth) ? ScrollBarWidth : ScrlBarHeight;
    u16 Step = (items - 1) ? (((ElementRect.Height - ScrlBarHeight) * 1000) / (items - 1)) : 0;
    s16 ScrlBarTop = ElementRect.Top + (Step * (FocusedLine)) / 1000;

    TGraphics::fillRect({ (s16)(ElementRect.Left + ElementRect.Width - 2),
                           ScrlBarTop ,
                            ScrollBarWidth,
                             ScrlBarHeight, 1 });
}

const u16 TVerticalContainer::getHeight(void) {
    return ElementRect.Height;
}

u16 TVerticalContainer::GetViewObjectsCount(){//���-�� �������� ����������� � ������ ���� �� FirstPosition �� ������� ����
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

void  TVerticalContainer::Clear(){//������� ������
  TComponentsContainer::Clear();
  FocusedLine = LastPosition = FirstPosition = 0;
}

TVerticalContainer::TVerticalContainer(TVerticalContainerProps& props, std::vector <TVisualObject*> Source)
    : TComponentsContainer(Source)
    , EnableScrollBar(props.EnableScrollBar)
    , FocusedLine(0)
    , FirstPosition(0)
    , LastPosition(1)
    , isOpen(false) {
      inFocus = false;
      ElementRect = { 0, 0, VIEW_PORT_MAX_HEIGHT, VIEW_PORT_MAX_WIDTH };
}

TVerticalContainer::~TVerticalContainer() {
};
