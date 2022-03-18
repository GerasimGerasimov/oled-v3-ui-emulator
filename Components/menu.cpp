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
const char LabelInitCaptionText[]="TLabel";

//����� "������ ������"
void  TLabel::View(){//������� ������ �� ������
  /*TTextProperty TextProperty = {
    //������� �������������� ���� ��������� ������� �����
    Left,//u16 MinLeft;
    Top,//u16 MinTop;
    Left+Width,//u16 MaxRight;  
    Top+Height,//u16 MaxBottom;
    //��������� ���������� ������ (������������ �������������� ���� ��������� ������� �����)
    //�.�. ��� ����� ���� � ��������������
    0,//s16 X;
    0,//s16 Y;
    //������������ ������
    //0 - ������� ����� � ����� ������� ��������������� ��������������
    //1 - ������� ����� � ������ ������� ��������������� ��������������
    //2 - ���������� ����� ����� � ������ ��������� ��������������� �������������� 
    0,//u8 Align;
    //���� ������
    TextColor,//u8 Color;
    //����� ���������� �������/������
    font,//FONT_INFO* font;
  };*/
  u8 i = 0;
  u8 j = 0;
  u8 c;

  u16 fone_color = NEG_COLOR;
  u16 text_color = BASIC_COLOR;
  
  if (Focus) {
    fone_color = BASIC_COLOR;
    text_color = NEG_COLOR;
  }
  
  //TextProperty.Color = text_color;
  TFillRect rect{ Left, Top, MAX_RIGHT, Height, fone_color };
  fillRect(rect);
  TTextProps textProps{ Left, Top, text_color, fone_color };
  outText(textProps, Caption);
}

u16 GetStrWidth(std::string s, const FONT_INFO* font) {//���������� ������ ������
    u16 w = 0;
    char* pC = (char*) s.c_str();
    while (*pC ++ != 0) {
        w += font->charInfo[*pC - 0x21].widthBits;
    }
    return w;
}

#define max_str_size 0x100 //������ ����, ����� ����������� �� ����� ������

u16 GetStrLength(char* s){//���������� ����� ������
  u16 l=0;
  while (*s++ != 0) {
    l++;
    //���� ������ ������ 255 ��������, �� ���������� � � 255
    //�������������� 255-� ���� ��� "0"
    if (l == max_str_size) break;
  }
  return l;
}

void TLabel::SetCaption(std::string NewCaption){//��������/�������� ����� � ������
    Caption = NewCaption;
}

TLabel::TLabel (std::string caption){//�����������
  Focus = false;
  //������������� ����������� ������
  SetCaption((caption != "")? caption : "default");
  //����a �� ���������
  TextColor = BASIC_COLOR;
  FoneColor = NEG_COLOR;
  //������� ������
  Left = 80;  //
  Top  = 0;   //
  //���� �� ���������
  font = &FontInfomSReferenceSansSerif6pt;
  Height = font->CharHeight;//������ ������ = ������ ������� � ������ ������
  Width = GetStrWidth(Caption, font); //������ ������ = ����� ����� �������� � ������
  //
}

TLabel::~TLabel (){//����������
}
