#ifndef MENU_H
#define MENU_H

#include <string>
#include <vector>
#include "stm32f4xx.h"
#include "msg.h"
#include "fonts.h"

class TVisualObject{//������� ����� ���������� ��������
  public:
    //���������� ����������� ������� � ������
    bool Focus;//false-�� � ������ true-� ������
    //������� ������ (������ �������� � �������� ������)
    s16 Left;  //
    s16 Top;   //
    u16 Height;//
    u16 Width; //
    virtual void View();//������� ������ �� ������
    TVisualObject ();//�����������
    virtual ~TVisualObject();//����������
};

class TVisualObjectsList{//������ ���������� �������� (���������)
  public:
    //������� ������ (������ �������� � �������� ������)
    u16 Left;  //
    u16 Top;   //
    u16 Height;//
    u16 Width; //
    u16 Count;//���������� �������� � ������
    void View();//������� ������ �� ������
    void Add(TVisualObject* pVisualObject);//�������� ������ � ������
    void Clear();//������� ������
    TVisualObjectsList ();//�����������
    virtual ~TVisualObjectsList();//����������
  private:
    std::vector <TVisualObject*> List;
};

//������ ������
class TLabel : public TVisualObject
{
public:
    const FONT_INFO* font;
    u16 TextColor;//���� ������ (0-������, 1-�����)
    u16 FoneColor;//���� ���� (0-������, 1-�����) (�����������)
    void View();//������� ������ �� ������
    void SetCaption(std::string NewCaption);//�������� ����� � ������ ������� � �����
    TLabel(std::string caption = "");//�����������
    ~TLabel();//����������
private:
    std::string Caption;//������ ��������� �������������� ������ ���������� ������    
};

class TMenu : public TVisualObject 
{
  public:
    bool isOpen;
    TLabel * Caption;//������ ��������� �������������� ������ ���������� ������ 
    //������� ������ (������ �������� � �������� ������)
    u16 Left;  //
    u16 Top;   //
    u16 Height;//
    u16 Width; //
    //� ����� �� ����� ������ ���� ��������, ���� ���-�� ����� �� ���������� �� �������
    u16 FocusLine;//������ ����������� � ������
    u16 FirstPosition;//������ ������������ ������ ������� �������� � ��
    u16 LastPosition; //��������� ������������ ������
    void View();//������� ������ �� ������
    void Add(TVisualObject* pVisualObject);//�������� ������ � ������
    void AddList(std::vector <TVisualObject*> Source);//�������� ������ �������� � ������
    void Clear();//������� ������
    void ProcessMessage(TMessage* m);//���������� ���������
    TMenu(std::string �aption, bool isOpenState, std::vector <TVisualObject*> Source = {});//�����������
    ~TMenu();//����������
    const u16& ItemsCount() const;
  private:
    std::vector <TVisualObject*> List;
    u16 GetViewObjectsCount();//���-�� �������� ����������� � ������ ���� �� FirstPosition �� ������� ����
    //u16 Items;//���������� �������� � ������
};

#endif