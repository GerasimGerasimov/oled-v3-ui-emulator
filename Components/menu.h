#ifndef MENU_H
#define MENU_H

#include <string>
#include <vector>
#include "common.h"
#include "stm32f4xx.h"
#include "msg.h"
#include "fonts.h"
#include "Label.h"

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