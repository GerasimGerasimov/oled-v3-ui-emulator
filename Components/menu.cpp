#include "menu.h"
#include "msg.h"

#include "graphics.h"

void TMenu::ProcessMessage(TMessage* m){//���������� ���������
  u16 Count = ItemsCount();
  if ( Count == 0) return;//�������� ������
    switch (m->Event) {
        case KEYBOARD:{//��������� �� ����������
            switch (m->p1) {
                case kbUp:{//������ �����
                    List[FocusLine]->Focus = false;//�������������� ���������� ������
                    if (FocusLine > 0) FocusLine--;
                    List[FocusLine]->Focus = true;//����������� ������
                    break;
                }
                case kbDown:{//������ ����
                    List[FocusLine]->Focus = false;//�������������� ���������� ������
                    if ((FocusLine < (Count -1)) && (Count !=0)) FocusLine++;
                    List[FocusLine]->Focus = true;//����������� ������
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

void TMenu::View(){//������� ������ �� ������
    if (isOpen == false) {
        if (Caption != NULL) {
            Caption->View();
            return;
        };
    };
    if (ItemsCount() == 0) return;//�������� ������
    //FillRect(Left, Top, Width, Height, 0);
    //����������, ������� ��������(�����) ��������� � ������ TMenu ������� � FirstPosition
    //��� ����, FocusLine ������ � ��������� ����� FirstPosition � LastPosition
    u16 c = GetViewObjectsCount();//���-�� �������� ����������� � ������ ���� �� FirstPosition �� ������� ����
                                //��� � ���� ���-�� �������� ��������� �� ����� (�� �� ������ ��� ����� �� �����������)
    u16 i = FirstPosition;//���-�� �������� ��������� �� �����
    u16 h = Top;//������� ���������� Y ������ ������
    //������ ��������� ������, � �������� ��������� ��������� ����� ��������� ���������� TMenu
    while (i != LastPosition) {//��������� �������� ���� � ������ ���-�� ���� 
    //����� ������� ������, ��������� ������ � ����������,
    //�������� ���������� Top � ����������� �� ������ ����������� �������
    List[i]->Left  = Left;  //����� ���������� �
    List[i]->Width = Width; //������ ������ = ������ ����������
    List[i]->Top  = h;      //����� ���������� Y
    h += List[i]->Height;   //���������� ���������� Y ��� ��������� ������
    List[i]->View();        //������ ��������� ������
    i++;                    //�������� � ��������� ������
    }
}

u16 TMenu::GetViewObjectsCount(){//���-�� �������� ����������� � ������ ���� �� FirstPosition �� ������� ����
//��� ���� ����������� �������
  if (FocusLine <= FirstPosition)  FirstPosition = FocusLine ;//���� ���� �������
  if ((FocusLine >= LastPosition) && (FocusLine < ItemsCount()))  FirstPosition++;//���� ���� ������, �� �� ������ ��� ���� � ������, �� ��������� �������
  u16 i = FirstPosition;
  u16 c = 0;//������� �����
  u16 h = 0; //������ �������
  while (h <= Height) {//
    if (i < ItemsCount()) {
      h += List[i]->Height;//���������� ������
      i++; //���������� ��������� �� ������
      c++; //���������� ���-�� ����� ����������� � ������� ����� ������
    }
    else {//��������� ������
      //if (c>0) c--;//�������� �����
      LastPosition = FirstPosition + c;//������� ����� ��������� ������������ ������
      return c;
    }
  }
  //������ ��������� ����������
  if (c>0) c--;//�������� �����
  LastPosition = FirstPosition + c;//������� ����� ��������� ������������ ������
  return c;
}

void TMenu::Add(TVisualObject* pVisualObject){//�������� ������ � ������
  List.push_back(pVisualObject);
}

void TMenu::AddList(std::vector <TVisualObject*> Source) {//�������� ������ �������� � ������
    List.assign(Source.begin(), Source.end());
}

void  TMenu::Clear(){//������� ������
  List.clear();
  FocusLine = LastPosition = FirstPosition = 0;
}

TMenu::TMenu (std::string �aption, bool isOpenState, std::vector <TVisualObject*> Source) {//�����������
  isOpen = isOpenState;
  Focus = false;
  FocusLine = FirstPosition = 0;
  LastPosition = 1;
  Left = Top = 0;//������� ����� ����
  Width  = MAX_RIGHT;  //������
  Height = MAX_BOTTOM; //������
  Caption = (�aption != "")
      ? new TLabel(�aption)
      : NULL;
  AddList(Source);
}

const u16& TMenu::ItemsCount() const {
    return List.size();
}

TMenu::~TMenu() {
    if (Caption != NULL) {
        delete(Caption);
    };
};

///////////////////////////////////////////////////////////////////////////////
//��������� (������) ���������� ��������
void TVisualObjectsList::View(){
  u16 i = List.size();//���-�� �������� � ������
  while (i != 0) {//��������� �������� ���� � ������ ����� ����
    i--; 
    List[i]->View();
  }
}

void TVisualObjectsList::Add(TVisualObject* pVisualObject){//�������� ������ � ������
  List.push_back(pVisualObject);
}

void TVisualObjectsList::Clear(){};//������� ������
TVisualObjectsList::TVisualObjectsList () {};
TVisualObjectsList::~TVisualObjectsList() {};

///////////////////////////////////////////////////////////////////////////////
//const char LabelInitCaptionText[]="TLabel";